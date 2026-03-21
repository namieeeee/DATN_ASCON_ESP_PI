#ifndef DS3231_H
#define DS3231_H

#include "driver/i2c_master.h"

#define DS3231_ADDR 0x68 // Địa chỉ I2C mặc định

typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;
} ds3231_time_t;

/**
 * @brief Initialize DS3231 with I2C master bus
 */
esp_err_t ds3231_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Get current time from DS3231
 */
esp_err_t ds3231_get_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time);

/**
 * @brief Set time for DS3231
 */
esp_err_t ds3231_set_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time);

#endif