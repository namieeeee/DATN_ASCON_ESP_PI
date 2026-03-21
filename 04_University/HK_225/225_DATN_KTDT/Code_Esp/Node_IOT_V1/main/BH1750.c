#include "BH1750.h"
#include "esp_log.h"

static const char *TAG = "BH1750";

esp_err_t bh1750_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = BH1750_ADDR_LO,
        .scl_speed_hz = 100000,
    };
    

    esp_err_t err = i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
    if (err != ESP_OK) return err;

   
    uint8_t cmd = BH1750_CONTINUOUS_HIGH_RES_MODE;
    return i2c_master_transmit(*dev_handle, &cmd, 1, -1);
}

esp_err_t bh1750_read_lux(i2c_master_dev_handle_t dev_handle, float *lux) {
    uint8_t data[2];
   
    esp_err_t err = i2c_master_receive(dev_handle, data, 2, -1);
    
    if (err == ESP_OK) {
        uint16_t raw_level = (data[0] << 8) | data[1];
        *lux = (float)raw_level / 1.2f; 
        return ESP_OK;
    }
    return err;
}