#ifndef DHT22_H
#define DHT22_H



#ifdef __cplusplus
extern "C" {
#endif
#include "driver/gpio.h"
// Define return error codes
#define DHT22_OK            0
#define DHT22_ERR_TIMEOUT  -1
#define DHT22_ERR_CHECKSUM -2

/**
 * @brief Read data from the DHT22 sensor
 * * @param pin GPIO pin connected to the DHT22 data line
 * @param temperature Pointer to store the returned temperature value
 * @param humidity Pointer to store the returned humidity value
 * @return int (DHT22_OK if successful, otherwise an error code)
 */
int dht22_read(gpio_num_t pin, float *temperature, float *humidity);

#ifdef __cplusplus
}
#endif

#endif // DHT22_H