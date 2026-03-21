/**
 * @file hal_sn34f7_crc.h
 * @author PD
 * @brief Define the private structure, option for SN34F7 HAL CRC.
 * @version 1.0
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _HAL_SN34F7_CRC_H_
#define _HAL_SN34F7_CRC_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_hal.h"

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
// check whether CRC instance is correct
#define IS_PERIPHERAL_CRC_INSTANCE(handler) (((handler)->instance) == SN_CRC)

#define IS_CRC_POLY(poly) (((poly) == CRC_POLY_CRC_16_CCITT) || ((poly) == CRC_POLY_CRC_16) || ((poly) == CRC_POLY_CRC_32))

#endif /* _HAL_SN34F7_CRC_H_ */
