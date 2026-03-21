#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "DHT22.h"
#include "DS3231.h"
#include "BH1750.h" 
#include "LCD_I2C.h"

static const char *TAG = "MAIN";
#define DHT22_PIN GPIO_NUM_3
void lcd_test_line1(i2c_master_dev_handle_t dev_handle, const char *text) {
    if (dev_handle == NULL) return;
    char buf[17];
    snprintf(buf, sizeof(buf), "%-16s", text); 
    lcd_put_cur(dev_handle, 0, 0);
    lcd_send_string(dev_handle, buf);
}

void lcd_test_line2(i2c_master_dev_handle_t dev_handle, const char *text) {
    if (dev_handle == NULL) return;
    char buf[17];
    snprintf(buf, sizeof(buf), "%-16s", text);
    lcd_put_cur(dev_handle, 1, 0);
}
void app_main(void)
{
    // 1. Config I2C Bus
    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = GPIO_NUM_6,
        .scl_io_num = GPIO_NUM_7,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true, 
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));

    // 2. Init handles with NULL
    i2c_master_dev_handle_t rtc_handle = NULL;
    i2c_master_dev_handle_t lux_handle = NULL; 
    i2c_master_dev_handle_t lcd_handle = NULL;
    
    // 3. Try to init devices (No ESP_ERROR_CHECK to avoid Panic)
    ds3231_init(bus_handle, &rtc_handle);
    bh1750_init(bus_handle, &lux_handle);
    lcd_init(bus_handle, &lcd_handle);

    ds3231_time_t now = {0};
    float temp = 0, hum = 0, lux = 0;
    char temp_buf[64];


    while (1) 
    {

		#if 1
        // --- READ RTC ---
        if (rtc_handle != NULL) { 
            if (ds3231_get_time(rtc_handle, &now) != ESP_OK) {
                ESP_LOGW(TAG, "RTC Connected but Read Error!");
            } else {
                ESP_LOGI(TAG, "TIME: %02d:%02d:%02d", now.hour, now.minute, now.second);
            }
        } else {
            ESP_LOGW(TAG, "RTC Handle is NULL - Check Connection");
        }

        // --- READ LUX ---
        if (lux_handle != NULL) {
            bh1750_read_lux(lux_handle, &lux);
        }

        // --- READ DHT22 ---
        dht22_read(DHT22_PIN, &temp, &hum);

        // --- DISPLAY LCD ---
        if (lcd_handle != NULL) {

            memset(temp_buf, 0, sizeof(temp_buf));
            snprintf(temp_buf, sizeof(temp_buf), "%02d:%02d:%02d  %.1fC", 
                     now.hour, now.minute, now.second, temp);
            lcd_put_cur(lcd_handle, 0, 0);
            lcd_send_string(lcd_handle, temp_buf);

            memset(temp_buf, 0, sizeof(temp_buf));
            snprintf(temp_buf, sizeof(temp_buf), "H:%.0f%%  L:%.0fLx   ", 
                     hum, lux);
            lcd_put_cur(lcd_handle, 1, 0);
            lcd_send_string(lcd_handle, temp_buf);
        }
        #if 0
if (lcd_handle != NULL) {
     
            memset(temp_buf, 0, sizeof(temp_buf));
            snprintf(temp_buf, sizeof(temp_buf), "Time:%02d:%02d:%02d ", now.hour, now.minute, now.second);
            lcd_put_cur(lcd_handle, 0, 0);
            lcd_send_string(lcd_handle, temp_buf);
            
       
            memset(temp_buf, 0, sizeof(temp_buf));
            snprintf(temp_buf, sizeof(temp_buf), "T:%.1f L:%.0f    ", temp, lux);
            lcd_put_cur(lcd_handle, 1, 0);
            lcd_send_string(lcd_handle, temp_buf);
        }
        #endif
        ESP_LOGI(TAG, "Status: T=%.1f, L=%.0f", temp, lux);
        ESP_LOGI(TAG, "-----------------------------------");
        vTaskDelay(pdMS_TO_TICKS(2500));
     #endif
    }
}