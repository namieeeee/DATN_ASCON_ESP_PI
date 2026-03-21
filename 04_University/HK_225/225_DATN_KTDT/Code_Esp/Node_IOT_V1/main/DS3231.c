#include "DS3231.h"


static uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
// Chuyển đổi Decimal sang BCD
static uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) + (val % 10); }

esp_err_t ds3231_init(i2c_master_bus_handle_t bus_handle, i2c_master_dev_handle_t *dev_handle) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DS3231_ADDR,
        .scl_speed_hz = 100000,
    };
    return i2c_master_bus_add_device(bus_handle, &dev_cfg, dev_handle);
}

esp_err_t ds3231_get_time(i2c_master_dev_handle_t dev_handle, ds3231_time_t *time) {
    uint8_t data[7];
    uint8_t reg = 0x00; 
    
    esp_err_t err = i2c_master_transmit_receive(dev_handle, &reg, 1, data, 7, -1);
    if (err != ESP_OK) return err;

    time->second = bcd2dec(data[0]);
    time->minute = bcd2dec(data[1]);
    time->hour   = bcd2dec(data[2] & 0x3F);
    time->day    = bcd2dec(data[3]);
    time->date   = bcd2dec(data[4]);
    time->month  = bcd2dec(data[5] & 0x7F);
    time->year   = bcd2dec(data[6]) + 2000;
    
    return ESP_OK;
}