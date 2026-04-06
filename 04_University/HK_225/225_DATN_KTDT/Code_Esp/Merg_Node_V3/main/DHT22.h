/******************************************************************************
 * @file    DHT22.h
 * @brief   Header file for the DHT22 Temperature and Humidity sensor driver.
 *
 * @details Provides function prototypes and error code definitions for 
 * interfacing with the DHT22 (AM2302) sensor using a single-wire 
 * bit-banging protocol on the ESP32.
 *
 * @author  Tran Nam
 * @date    2026-03-21
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
 
#ifndef DHT22_H
#define DHT22_H



#ifdef __cplusplus
extern "C" {
#endif
#include "driver/gpio.h"
// Define return error codes
#define DHT22_OK            0 /*!< Success: Data read and checksum verified */
#define DHT22_ERR_TIMEOUT  -1 /*!< Success: Data read and checksum verified */
#define DHT22_ERR_CHECKSUM -2 /*!< Success: Data read and checksum verified */

/**
 * @brief Read temperature and humidity data from the DHT22 sensor.
 * @details This function triggers a start signal to the sensor, waits for the 
 * response, and then reads 40 bits of data. It calculates the checksum 
 * and converts the raw data into floating-point Celsius and Humidity values.
 * @note This function is timing-sensitive and uses critical sections internally.
 * @param[in]  pin          The GPIO number used for the 1-wire data bus.
 * @param[out] temperature  Pointer to a float to store temperature (in °C).
 * @param[out] humidity     Pointer to a float to store relative humidity (in %).
 * @return int 
 * - DHT22_OK: Success.
 * - DHT22_ERR_TIMEOUT: Sensor failed to respond or pulse was too long.
 * - DHT22_ERR_CHECKSUM: Received data is invalid.
 */
int dht22_read(gpio_num_t pin, float *temperature, float *humidity);

#ifdef __cplusplus
}
#endif

#endif // DHT22_H