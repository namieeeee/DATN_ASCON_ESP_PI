#ifndef BH1750_H
#define BH1750_H

#include "driver/i2c_master.h"
#include "esp_err.h"

#define BH1750_ADDR_LO          0x23   
#define BH1750_ADDR_HI          0x5C   


#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10 
#define BH1750_POWER_ON                  0x01
#define BH1750_RESET                     0x07

/**
 * @brief init  BH1750 sensor
 */
esp_err_t bh1750_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle);

/**
 * @brief 
 */
esp_err_t bh1750_read_lux(i2c_master_dev_handle_t dev_handle, float *lux);

#endif