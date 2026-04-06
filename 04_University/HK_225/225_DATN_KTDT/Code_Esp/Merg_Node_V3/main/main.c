/******************************************************************************
 * @file    main.c
 * @brief   Core Application for Secure IoT Sensor Node.
 *
 * @details This application implements a multitasking system using FreeRTOS on 
 * ESP32. It performs real-time data acquisition from various sensors (DHT22, 
 * BH1750, DS3231), visualizes data on an I2C LCD, and ensures data security 
 * using the Ascon-128 Authenticated Encryption (AEAD) before transmitting 
 * the payload via UART LoRa.
 *
 * @author  Tran Nam
 * @date    2026-04-06
 * @version 1.0
 *
 * @note
 * - OS: FreeRTOS (Task-based architecture).
 * - Security: Ascon-128 (NIST LWC Standard).
 * - Hardware: ESP32 SoC with I2C and UART peripherals.
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/* FreeRTOS includes */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* ESP-IDF includes */
#include "esp_log.h"
#include "esp_err.h"
#include "driver/i2c_master.h"
#include "driver/uart.h"
#include "esp_random.h"

/* Project Component includes */
#include "DHT22.h"
#include "DS3231.h"
#include "BH1750.h" 
#include "LCD_I2C.h"

#include "ascon.h"

static const char *TAG = "MAIN_APP";

/* Hardware Pin Definitions */
#define DHT22_PIN           GPIO_NUM_3
#define UART_PORT_NUM       UART_NUM_1
#define UART_TX_PIN         GPIO_NUM_5
#define UART_RX_PIN         GPIO_NUM_4
#define UART_BAUD_RATE      9600 // 115200 9600


 /** 
 * @brief Global 128-bit Secret Key for Ascon encryption.
 * @warning In a production environment, this should be stored securely (NVS/eFuse).
 */
static const uint8_t g_key[CRYPTO_KEYBYTES] = {
    0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE,
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

 /** 
 * @brief Structure to store synchronized sensor readings.
 */
typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    float temp;
    float hum;
    float lux;
} sensor_data_t;

/* FreeRTOS Queue for inter-task communication */
QueueHandle_t sensor_queue;

/* I2C Device Handles */
i2c_master_dev_handle_t rtc_handle = NULL;
i2c_master_dev_handle_t lux_handle = NULL; 
i2c_master_dev_handle_t lcd_handle = NULL;

// ============================================================================
// SENSOR TASK: Handles data acquisition and local display
// ============================================================================
void sensor_task(void *pvParameters) {
    ds3231_time_t now = {0};
    sensor_data_t data_packet = {0};
    char temp_buf[64];

    while (1) 
    {
		/* 1. Retrieve Real-Time Clock data */
        if (rtc_handle != NULL && ds3231_get_time(rtc_handle, &now) == ESP_OK) {
            data_packet.hour = now.hour;
            data_packet.minute = now.minute;
            data_packet.second = now.second;
        }
        
        /* 2. Retrieve Ambient Light intensity */
        if (lux_handle != NULL)
        {
            bh1750_read_lux(lux_handle, &data_packet.lux);
        }
        
        /* 3. Retrieve Temperature & Humidity */
        dht22_read(DHT22_PIN, &data_packet.temp, &data_packet.hum);
        
        /* 4. Update Local LCD Display */
        if (lcd_handle != NULL) 
        {
            memset(temp_buf, 0, sizeof(temp_buf));
            // Line 0: HH:MM:SS and Temperature
            snprintf(temp_buf, sizeof(temp_buf), "%02d:%02d:%02d  %.1fC", 
                     now.hour, now.minute, now.second, data_packet.temp);
            lcd_put_cur(lcd_handle, 0, 0);
            lcd_send_string(lcd_handle, temp_buf);

            memset(temp_buf, 0, sizeof(temp_buf));
            // Line 1: Humidity and Lux
            snprintf(temp_buf, sizeof(temp_buf), "H:%.0f%%  L:%.0fLx   ", 
                     data_packet.hum, data_packet.lux);
            lcd_put_cur(lcd_handle, 1, 0);
            lcd_send_string(lcd_handle, temp_buf);
        }

        ESP_LOGI(TAG, "Sensor Read: T=%.1f, H=%.1f, L=%.0f", data_packet.temp, data_packet.hum, data_packet.lux); // DEBUG
        
        /* 5. Pass data to Crypto Task via Queue */
        xQueueSend(sensor_queue, &data_packet, pdMS_TO_TICKS(100));
        vTaskDelay(pdMS_TO_TICKS(1000));  // Sample rate: 1Hz
    }
}

// ============================================================================
// CRYPTO & UART TASK: Handles Ascon encryption and LoRa transmission
// ============================================================================

void crypto_uart_task(void *pvParameters) 
{
    sensor_data_t recv_data;
    uint8_t nonce[CRYPTO_NPUBBYTES];
    
    /* UART Configuration for LoRa Module */
    uart_config_t uart_config = 
    {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    
    uart_param_config(UART_PORT_NUM, &uart_config);
    
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    
    uart_driver_install(UART_PORT_NUM, 1024, 1024, 0, NULL, 0);

    while (1) 
    {   
		/* Wait indefinitely for data from the sensor_task */
        if (xQueueReceive(sensor_queue, &recv_data, portMAX_DELAY) == pdPASS) 
        {
            char payload[128];
            int payload_len = snprintf(payload, sizeof(payload), 
                                       "Time:%02d:%02d:%02d,T:%.1f,H:%.1f,L:%.0f", 
                                       recv_data.hour, recv_data.minute, recv_data.second,
                                       recv_data.temp, recv_data.hum, recv_data.lux);
                                       
             if (payload_len >= sizeof(payload)) {
                  payload_len = sizeof(payload) - 1; 
             }     

            uint8_t ciphertext[128 + CRYPTO_ABYTES]; 
            unsigned long long clen = 0;

            /* 1. Generate Hardware-Based Random Nonce (Public Message Number) */
            uint32_t *rand_ptr = (uint32_t *)nonce;
            for (int i = 0; i < 4; i++) 
            {
                rand_ptr[i] = esp_random(); 
            }
            
            /* 2. Execute Ascon-128 Encryption */
            if (crypto_aead_encrypt(ciphertext, &clen,
                                    (const uint8_t *)payload, payload_len,
                                    NULL, 0, 
                                    NULL, nonce, g_key) == 0) 
            {
                ESP_LOGI(TAG, "ASCON Encrypt Success! Length: %llu bytes", clen);
                
            /* 3. Format Frame: ASCON:[NONCE][CIPHERTEXT]\n */
                char hex_str[512] = {0}; 
                int hex_pos = 0;
                
                hex_pos += sprintf(hex_str + hex_pos, "ASCON:");
                
            // Append Nonce (Mandatory for decryption at receiver)
                for(int i = 0; i < CRYPTO_NPUBBYTES; i++) 
                {
                   hex_pos += sprintf(hex_str + hex_pos, "%02X", nonce[i]);
                }
                
            // Append Ciphertext (includes the Authentication Tag)
                for(int i = 0; i < clen; i++) 
                {
                    hex_pos += sprintf(hex_str + hex_pos, "%02X", ciphertext[i]);
                }

                hex_pos += sprintf(hex_str + hex_pos, "\n");
                
           /* 4. Transmit secure frame via LoRa */
                uart_write_bytes(UART_PORT_NUM, hex_str, hex_pos);
                
                ESP_LOGI(TAG, "Sent HEX via LoRa: %s", hex_str);
            } else 
            {
                ESP_LOGE(TAG, "ASCON Encrypt Failed!");
            }
        }
    }
}

// ============================================================================
// MAIN: System Initialization
// ============================================================================

void app_main(void)
{
	/* Initialize I2C Master Bus */
    i2c_master_bus_config_t bus_cfg = 
    {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = GPIO_NUM_6,
        .scl_io_num = GPIO_NUM_7,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true, 
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));

    /* Initialize Peripherals on I2C Bus */
    ds3231_init(bus_handle, &rtc_handle);
    bh1750_init(bus_handle, &lux_handle);
    lcd_init(bus_handle, &lcd_handle);
    
    /* Create Queue for Inter-Task Communication (Buffer size: 5 packets) */
    sensor_queue = xQueueCreate(5, sizeof(sensor_data_t));
    if (sensor_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }
    
    /* Launch Multitasking Environment */
    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    xTaskCreate(crypto_uart_task, "crypto_uart_task", 4096, NULL, 5, NULL);
}