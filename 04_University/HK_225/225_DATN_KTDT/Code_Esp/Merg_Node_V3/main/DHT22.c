/******************************************************************************
 * @file    DHT22.c
 * @brief   Driver implementation for the DHT22 Temperature & Humidity Sensor.
 *
 * @details This file implements the bit-banging protocol required to interface 
 * with the DHT22 sensor on ESP32. It handles the start signal, response 
 * verification, and 40-bit data acquisition with checksum validation.
 *
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @note    - Uses esp_timer for microsecond precision.
 * - Critical sections are used to prevent FreeRTOS task switching 
 * during sensitive timing windows.
 *
 * @warning Ensure the GPIO used has an external pull-up resistor if the 
 * internal one is insufficient for long cables.
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/

#include "DHT22.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h" 

#define TIMEOUT_US 1000
static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
static const char *TAG = "DHT22_DRV";

/**
 * @brief Helper function to wait for a specific GPIO state with timeout.
 * @return Time elapsed in microseconds, or -1 if timeout occurred.
 */

static int wait_for_state(gpio_num_t pin, int state) {
    int64_t start_time = esp_timer_get_time();
    while (gpio_get_level(pin) != state) {
        if (esp_timer_get_time() - start_time > TIMEOUT_US) {
            return -1;
        }
    }
    return (int)(esp_timer_get_time() - start_time);
}

/**
 * @brief Read temperature and humidity from DHT22 sensor.
 * @param[in]  pin          GPIO number connected to DHT22 data pin.
 * @param[out] temperature  Pointer to store the converted Celsius value.
 * @param[out] humidity     Pointer to store the converted Relative Humidity (%).
 * @return int              DHT22_OK on success, or error code (TIMEOUT/CHECKSUM).
 */

int dht22_read(gpio_num_t pin, float *temperature, float *humidity) {
    uint8_t data[5] = {0};

    /* 1. Send Start Signal */
    // Set pin to Output and pull low for ~20ms
    gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);

    gpio_set_level(pin, 0);
    esp_rom_delay_us(20000);

    // Pull high and wait for sensor response
    gpio_set_level(pin, 1);
    esp_rom_delay_us(30);
    
    /* 2. Critical Section: Disable interrupts for precise timing */
    taskENTER_CRITICAL(&mux);
    
    // Sensor should pull low, then high, then low again to signal readiness
    if (wait_for_state(pin, 0) < 0 ||
        wait_for_state(pin, 1) < 0 ||
        wait_for_state(pin, 0) < 0) 
        {
	        taskEXIT_CRITICAL(&mux);
	        return DHT22_ERR_TIMEOUT;
        }

    /* 3. Data Acquisition (40 bits) */
    for (int i = 0; i < 40; i++) 
    {
		// Wait for the high pulse which starts each bit
        if (wait_for_state(pin, 1) < 0) 
        {
            taskEXIT_CRITICAL(&mux);
            return DHT22_ERR_TIMEOUT;
        }
        
        // Measure the duration of the high pulse
        int high_time = wait_for_state(pin, 0);
        if (high_time < 0) 
        {
            taskEXIT_CRITICAL(&mux); 
            return DHT22_ERR_TIMEOUT;
        }
        
        /* Logic: pulse > 40us means bit '1', else bit '0' */
        if (high_time > 40) {
            data[i / 8] |= (1 << (7 - (i % 8))); // End of timing-critical part
        }
    }

    taskEXIT_CRITICAL(&mux);

    //  ESP_LOGI(TAG, " %02X %02X %02X %02X %02X", data[0], data[1], data[2], data[3], data[4]);  // DEBUG

    /* 4. Checksum Validation */
    // Last byte must be the 8-bit sum of the first four bytes  
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) 
    {
        return DHT22_ERR_CHECKSUM;
    }

    /* 5. Data Conversion */
    // Humidity: 16-bit value (0.1% unit)
    *humidity = ((data[0] << 8) | data[1]) * 0.1;
    
    // Temperature: 16-bit value (0.1°C unit), MSB (bit 15) is sign bit
    int temp_raw = ((data[2] & 0x7F) << 8) | data[3];
    
    *temperature = temp_raw * 0.1;
    if (data[2] & 0x80) *temperature = -*temperature;


    return DHT22_OK;
}