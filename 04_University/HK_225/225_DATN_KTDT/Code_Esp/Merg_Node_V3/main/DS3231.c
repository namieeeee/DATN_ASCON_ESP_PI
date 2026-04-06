
/******************************************************************************
 * @file    DS3231.c
 * @brief   Driver implementation for the DS3231 Real-Time Clock (RTC).
 *
 * @details This file provides functions to initialize and retrieve time from 
 * the DS3231 sensor via I2C. It includes helper functions for BCD-to-Decimal 
 * conversion to ensure human-readable time formats.
 *
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
 
#include "DS3231.h"

/**
 * @brief Converts a BCD byte to a standard Decimal byte.
 * @param val BCD encoded value (e.g., 0x25 for 25).
 * @return Standard decimal value (e.g., 25).
 */
 
static uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }

/**
 * @brief Converts a standard Decimal byte to BCD format.
 * @param val Standard decimal value (e.g., 25).
 * @return BCD encoded value (e.g., 0x25).
 */
static uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) + (val % 10); }

/**
 * @brief Initialize the DS3231 RTC and add it to the I2C bus.
 * @param[in]  bus_handle  Handle of the existing I2C master bus.
 * @param[out] dev_handle  Pointer to store the allocated I2C device handle.
 * @return esp_err_t       ESP_OK on success, or I2C error code.
 */
esp_err_t ds3231_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) 
{    
	/* Configuration for DS3231 I2C Slave */
    i2c_device_config_t dev_cfg = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DS3231_ADDR, // Default address (0x68)
        .scl_speed_hz = 100000,        // Standard Mode (100kHz)
    };
    
    /* Register the device on the I2C bus */
    return i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
}

/**
 * @brief Retrieve current date and time from DS3231.
 * @details Reads 7 bytes starting from register 0x00 (Seconds) to 0x06 (Year).
 * @param[in]  dev_handle  The I2C device handle for DS3231.
 * @param[out] time        Pointer to a structure to store the decoded time.
 * @return esp_err_t       ESP_OK on success.
 */
esp_err_t ds3231_get_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time) 
{
    uint8_t data[7];
    uint8_t reg = 0x00; // Start reading from the Seconds register
    
    /* Perform I2C transmit-receive: send register address, then read 7 bytes */
    esp_err_t err = i2c_master_transmit_receive(dev_handle, &reg, 1, data, 7, -1);
    if (err != ESP_OK) return err;
    
    /* Decode BCD values into decimal, applying specific masks where needed */
    time->second = bcd2dec(data[0]);
    time->minute = bcd2dec(data[1]);
    time->hour   = bcd2dec(data[2] & 0x3F); // Mask bits 0-5 for 24-hour format
    time->day    = bcd2dec(data[3]);        // Day of week
    time->date   = bcd2dec(data[4]);        // Day of month
    time->month  = bcd2dec(data[5] & 0x7F); // Mask bit 7 (Century bit)
    time->year   = bcd2dec(data[6]) + 2000; // Year is 00-99, offset by 2000
    
    return ESP_OK;
}