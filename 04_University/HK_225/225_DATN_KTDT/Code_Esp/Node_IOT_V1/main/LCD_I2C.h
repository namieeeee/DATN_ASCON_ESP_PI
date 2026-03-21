#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "driver/i2c_master.h"

#define LCD_ADDR 0x27 // Thường là 0x27 hoặc 0x3F
#define LCD_COLS 16
#define LCD_ROWS 2

esp_err_t lcd_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);
void lcd_put_cur(i2c_master_dev_handle_t dev_handle, int row, int col);
void lcd_send_string(i2c_master_dev_handle_t dev_handle, char *str);
void lcd_clear(i2c_master_dev_handle_t dev_handle);

#endif