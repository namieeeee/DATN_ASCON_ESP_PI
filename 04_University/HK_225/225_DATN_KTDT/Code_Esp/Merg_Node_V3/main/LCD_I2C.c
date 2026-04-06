/******************************************************************************
 * @file    LCD_I2C.c
 * @brief   Driver implementation for Liquid Crystal Display (LCD 16x2/20x4) via I2C.
 *
 * @details This driver interfaces with Hitach HD44780-compatible LCDs using 
 * the PCF8574 I2C expander. It implements the 4-bit communication protocol 
 * to save GPIO pins on the ESP32.
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/

#include "LCD_I2C.h"
#include "rom/ets_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* LCD Control Bits (Mapped to PCF8574 output pins) */

#define LCD_CMD   0x00 /*!< Command mode (RS = 0) */
#define LCD_DATA  0x01 /*!< Data mode (RS = 1) */
#define EN        0x04 /*!< Enable bit (Pulse to latch data) */ 
#define RS        0x01 /*!< Register Select bit */ 
#define BACKLIGHT 0x08 /*!< Backlight control bit (1 = ON) */


/**
 * @brief Internal function to transmit a single byte to the I2C expander.
 */
static esp_err_t lcd_send_internal(i2c_master_dev_handle_t dev_handle, uint8_t data) 
{
    return i2c_master_transmit(dev_handle, &data, 1, -1);
}

/**
 * @brief Sends a command or data byte to the LCD using 4-bit mode.
 * @details Splitting the 8-bit value into high and low nibbles. Each nibble 
 * is sent with an Enable (EN) pulse to latch the data.
 */
static void lcd_send(i2c_master_dev_handle_t dev_handle, uint8_t val, uint8_t mode) 
{
    uint8_t high_nibble = val & 0xF0;
    uint8_t low_nibble = (val << 4) & 0xF0;
    
    /* Process High Nibble */
    // Send nibble with EN high, then EN low to create the falling edge trigger
    uint8_t data_h[2] = {high_nibble | mode | BACKLIGHT | EN, high_nibble | mode | BACKLIGHT};
    i2c_master_transmit(dev_handle, data_h, 2, -1);
    ets_delay_us(50); 
    
    /* Process Low Nibble */
    uint8_t data_l[2] = {low_nibble | mode | BACKLIGHT | EN, low_nibble | mode | BACKLIGHT};
    i2c_master_transmit(dev_handle, data_l, 2, -1);
    ets_delay_us(50);
}

/**
 * @brief Initialize the LCD into 4-bit mode and configure display settings.
 * @return esp_err_t ESP_OK on successful initialization.
 */
esp_err_t lcd_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = LCD_ADDR,
        .scl_speed_hz = 100000,
    };
    
    /* Add LCD to I2C bus */
    esp_err_t err = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (err != ESP_OK) return err;

    /* Sequence to initialize LCD in 4-bit mode (Standard HD44780 procedure) */
    vTaskDelay(pdMS_TO_TICKS(50));
    lcd_send(*dev_handle, 0x33, LCD_CMD); // Initialize
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_send(*dev_handle, 0x32, LCD_CMD); // Set to 4-bit mode
    vTaskDelay(pdMS_TO_TICKS(5));
    
    /* Display Configuration */ 
    lcd_send(*dev_handle, 0x28, LCD_CMD);  // 2 lines, 5x8 matrix
    lcd_send(*dev_handle, 0x0C, LCD_CMD);  // Display ON, Cursor OFF
    lcd_send(*dev_handle, 0x06, LCD_CMD);  // Increment cursor
    lcd_send(*dev_handle, 0x01, LCD_CMD);  // Clear display
    vTaskDelay(pdMS_TO_TICKS(5));
    
    return ESP_OK;
}

/**
 * @brief Move the cursor to a specific row and column.
 * @param row Row index (0 or 1).
 * @param col Column index (0 to 15).
 */
 
void lcd_put_cur(i2c_master_dev_handle_t dev_handle, int row, int col) 
{
    uint8_t pos = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send(dev_handle, pos, LCD_CMD);
}

/**
 * @brief Print a null-terminated string to the LCD.
 */
void lcd_send_string(i2c_master_dev_handle_t dev_handle, char *str) 
{
    while (*str) {
        lcd_send(dev_handle, (uint8_t)(*str++), LCD_DATA);
    }
}

/**
 * @brief Clear all content from the display.
 */
void lcd_clear(i2c_master_dev_handle_t dev_handle) 
{
    lcd_send(dev_handle, 0x01, LCD_CMD);
    vTaskDelay(pdMS_TO_TICKS(2)); // Clearing requires extra time
}