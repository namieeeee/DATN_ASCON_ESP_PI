/******************************************************************************
 * @file    DS3231.h
 * @brief   Header file for the DS3231 High-Precision Real-Time Clock (RTC).
 *
 * @details This driver provides an interface to manage time and date via I2C.
 * The DS3231 is a temperature-compensated RTC, ensuring minimal drift 
 * over time, suitable for long-term data logging on ESP32.
 *
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
 
#ifndef DS3231_H
#define DS3231_H

#include "driver/i2c_master.h"

/**
 * @brief Default I2C Slave Address for DS3231
 */
#define DS3231_ADDR 0x68 

typedef struct {
    uint8_t second; /*!< Seconds (0-59) */
    uint8_t minute; /*!< Minutes (0-59) */
    uint8_t hour;   /*!< Hours (0-23 in 24h format) */
    uint8_t day;    /*!< Day of the week (1-7, 1=Sunday) */
    uint8_t date;   /*!< Day of the month (1-31) */
    uint8_t month;  /*!< Month (1-12) */
    uint16_t year;  /*!< Year (e.g., 2026) */
} ds3231_time_t;

/**
 * @brief Initialize the DS3231 device on the I2C master bus.
 * @param[in]  bus_handle  The handle of the initialized I2C master bus.
 * @param[out] dev_handle  Pointer to store the created I2C device handle.
 * @return esp_err_t       ESP_OK on success, or ESP error code on failure.
 */
esp_err_t ds3231_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Retrieve the current date and time from the DS3231 registers.
 * * @param[in]  dev_handle  The I2C device handle for the DS3231.
 * @param[out] time        Pointer to a ds3231_time_t structure to be populated.
 * @return esp_err_t       ESP_OK if reading and BCD decoding were successful.
 */
esp_err_t ds3231_get_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time);

/**
 * @brief Update the DS3231 internal registers with new time and date values.
 * @details This function converts the decimal values in the structure to BCD 
 * before transmitting them to the sensor's memory (starting from address 0x00).
 * @param[in]  dev_handle  The I2C device handle for the DS3231.
 * @param[in]  time        Pointer to a ds3231_time_t structure containing new time.
 * @return esp_err_t       ESP_OK on successful update.
 */
esp_err_t ds3231_set_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time);

#endif