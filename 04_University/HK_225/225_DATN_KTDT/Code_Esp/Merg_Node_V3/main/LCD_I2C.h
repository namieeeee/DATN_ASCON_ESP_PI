/******************************************************************************
 * @file    LCD_I2C.h
 * @brief   Header file for the I2C-based LCD (16x2/20x4) driver.
 *
 * @details Defines the standard API for initializing and controlling an 
 * HD44780-compatible LCD through a PCF8574 I2C expander module.
 *
 * @author  Tran Nam
 * @date    2026-04-06
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
 
#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "driver/i2c_master.h"

#define LCD_ADDR 0x27 /* Default I2C address for most PCF8574 modules */
#define LCD_COLS 16   /* Number of columns (typical 16x2 LCD) */
#define LCD_ROWS 2    /* Number of rows (typical 16x2 LCD) */

/**
 * @brief Initialize the LCD module.
 * @details Sets up the I2C device configuration and performs the power-on 
 * initialization sequence to set the LCD to 4-bit mode.
 * @param[in]  bus_handle  The handle of the initialized I2C master bus.
 * @param[out] dev_handle  Pointer to hold the created I2C device handle.
 * @return esp_err_t       ESP_OK on success, or ESP error code on failure.
 */
esp_err_t lcd_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Set the cursor position on the display.
 * @param[in] dev_handle  The I2C device handle for the LCD.
 * @param[in] row         Row index (0-based, 0 to LCD_ROWS-1).
 * @param[in] col         Column index (0-based, 0 to LCD_COLS-1).
 */
void lcd_put_cur(i2c_master_dev_handle_t dev_handle, int row, int col);

/**
 * @brief Print a string of characters to the LCD at the current cursor position.
 * @param[in] dev_handle  The I2C device handle for the LCD.
 * @param[in] str         Null-terminated string to be displayed.
 */
void lcd_send_string(i2c_master_dev_handle_t dev_handle, char *str);

/**
 * @brief Clear the display and return the cursor to the home position (0,0).
 * @param[in] dev_handle  The I2C device handle for the LCD.
 */
void lcd_clear(i2c_master_dev_handle_t dev_handle);

#endif /* LCD_I2C_H */