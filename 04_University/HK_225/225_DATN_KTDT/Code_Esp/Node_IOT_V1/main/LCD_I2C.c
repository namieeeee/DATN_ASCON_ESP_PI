#include "LCD_I2C.h"
#include "rom/ets_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define LCD_CMD 0x00
#define LCD_DATA 0x01
#define EN 0x04  
#define RS 0x01  
#define BACKLIGHT 0x08 


static esp_err_t lcd_send_internal(i2c_master_dev_handle_t dev_handle, uint8_t data) {
    return i2c_master_transmit(dev_handle, &data, 1, -1);
}


static void lcd_send(i2c_master_dev_handle_t dev_handle, uint8_t val, uint8_t mode) {
    uint8_t high_nibble = val & 0xF0;
    uint8_t low_nibble = (val << 4) & 0xF0;
    
    uint8_t data_h[2] = {high_nibble | mode | BACKLIGHT | EN, high_nibble | mode | BACKLIGHT};
    i2c_master_transmit(dev_handle, data_h, 2, -1);
    ets_delay_us(50); 

    uint8_t data_l[2] = {low_nibble | mode | BACKLIGHT | EN, low_nibble | mode | BACKLIGHT};
    i2c_master_transmit(dev_handle, data_l, 2, -1);
    ets_delay_us(50);
}

esp_err_t lcd_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = LCD_ADDR,
        .scl_speed_hz = 100000,
    };
    
    esp_err_t err = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (err != ESP_OK) return err;


    vTaskDelay(pdMS_TO_TICKS(50));
    lcd_send(*dev_handle, 0x33, LCD_CMD);
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_send(*dev_handle, 0x32, LCD_CMD);
    vTaskDelay(pdMS_TO_TICKS(5));
    
    lcd_send(*dev_handle, 0x28, LCD_CMD); 
    lcd_send(*dev_handle, 0x0C, LCD_CMD); 
    lcd_send(*dev_handle, 0x06, LCD_CMD); 
    lcd_send(*dev_handle, 0x01, LCD_CMD); 
    vTaskDelay(pdMS_TO_TICKS(5));
    
    return ESP_OK;
}

void lcd_put_cur(i2c_master_dev_handle_t dev_handle, int row, int col) {
    uint8_t pos = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send(dev_handle, pos, LCD_CMD);
}

void lcd_send_string(i2c_master_dev_handle_t dev_handle, char *str) {
    while (*str) {
        lcd_send(dev_handle, (uint8_t)(*str++), LCD_DATA);
    }
}

void lcd_clear(i2c_master_dev_handle_t dev_handle) {
    lcd_send(dev_handle, 0x01, LCD_CMD);
    vTaskDelay(pdMS_TO_TICKS(2));
}