/******************************************************************************
 * @file    BH1750.c
 * @brief   Driver implementation for the BH1750 Digital Light Sensor.
 *
 * @details This file provides functions to initialize the BH1750 sensor via 
 * the ESP32 I2C master driver and read ambient light intensity in Lux.
 *
 * @author  Tran Nam
 * @date    2026-03-28
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
#include "BH1750.h"
#include "esp_log.h"

static const char *TAG = "BH1750";

/**
 * @brief Initialize the BH1750 sensor and add it to the I2C bus.
 * * @param[in]  bus_handle  Handle of the existing I2C master bus.
 * @param[out] dev_handle  Pointer to store the allocated I2C device handle.
 * @return esp_err_t       ESP_OK on success, or error code on failure.
 */
 
esp_err_t bh1750_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) 
{
	/* Configure I2C device parameters for BH1750 */
    i2c_device_config_t dev_cfg = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = BH1750_ADDR_LO, // Default address (0x23)
        .scl_speed_hz = 100000,           // Standard I2C speed (100kHz)
    };
    
   /* Add BH1750 as a device on the I2C master bus */
    esp_err_t err = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (err != ESP_OK) return err;

   /* Power on and set to Continuous High Resolution Mode (1lx resolution) */
    uint8_t cmd = BH1750_CONTINUOUS_HIGH_RES_MODE;
    return i2c_master_transmit(*dev_handle, &cmd, 1, -1);
}

/**
 * @brief Read the ambient light intensity in Lux.
 * * @param[in]  dev_handle  The I2C device handle for BH1750.
 * @param[out] lux         Pointer to store the calculated illuminance value.
 * @return esp_err_t       ESP_OK if reading was successful.
 */
 
esp_err_t bh1750_read_lux(i2c_master_dev_handle_t dev_handle, float *lux) {
    uint8_t data[2];
    
   /* Receive 2 bytes of raw data from the sensor */
    esp_err_t err = i2c_master_receive(dev_handle, data, 2, -1);
    
    if (err == ESP_OK) 
    {   /* Combine two bytes into a 16-bit unsigned integer (Big Endian) */
        uint16_t raw_level = (data[0] << 8) | data[1];
        
        /* Convert raw value to Lux using the datasheet formula: Lux = Raw / 1.2 */
        *lux = (float)raw_level / 1.2f; 
        return ESP_OK;
    }
    //ESP_LOGE(TAG, "Failed to read data from BH1750");
    return err;
}