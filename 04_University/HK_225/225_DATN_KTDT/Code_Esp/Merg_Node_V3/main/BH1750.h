/******************************************************************************
 * @file    BH1750.h
 * @brief   Header file for the BH1750 Ambient Light Sensor driver.
 *
 * @details Contains I2C addresses, command opcodes, and function prototypes 
 * for interfacing with the BH1750 sensor on the ESP32 platform.
 *
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
 
 
#ifndef BH1750_H
#define BH1750_H

#include "driver/i2c_master.h"
#include "esp_err.h"

/** * @name BH1750 I2C Slave Addresses
 * @{ 
 */
#define BH1750_ADDR_LO          0x23    /*!< ADDR pin connected to GND */
#define BH1750_ADDR_HI          0x5C   /*!< ADDR pin connected to VCC */
/** @} */

/** * @name BH1750 Instruction Opcodes
 * @{ 
 */
#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10 /*!< Continuous H-Resolution Mode (1lx resolution, 120ms meas. time) */
#define BH1750_POWER_ON                  0x01 /*!< Waiting for measurement command */
#define BH1750_RESET                     0x07 /*!< Reset Data register value (not valid in Power Down mode) */
/** @} */
/**
 * @brief Initialize the BH1750 sensor.
 * @details Configures the I2C device parameters, adds the device to the master bus,
 * and sets the sensor to Continuous High Resolution mode.
 * @param[in]  bus_handle  Handle of the initialized I2C master bus.
 * @param[out] dev_handle  Pointer to hold the created I2C device handle.
 * @return esp_err_t       ESP_OK on success, ESP_FAIL or I2C error code otherwise.
 */
 
esp_err_t bh1750_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief Read illuminance data from the BH1750 sensor.
 * @details Triggers an I2C read transaction, combines the 2-byte response, 
 * and converts the raw value into Lux (lx).
 * @param[in]  dev_handle  The I2C device handle for the BH1750.
 * @param[out] lux         Pointer to a float where the calculated Lux value will be stored.
 * @return esp_err_t       ESP_OK on success, ESP_ERR_TIMEOUT or I2C error code otherwise.
 */
esp_err_t bh1750_read_lux(i2c_master_dev_handle_t dev_handle, float *lux);

#endif