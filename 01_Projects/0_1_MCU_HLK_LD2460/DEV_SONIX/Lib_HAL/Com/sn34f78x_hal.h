/**
 * @file sn34f78x_hal.h
 * @author PD
 * @brief define the public information for SN34F78x HAL SDK
 * @version 1.0
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _SN34F78X_HAL_H_
#define _SN34F78X_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/** sn34f78x_hal_conf.h MUST be supplied in project to enable the peripheral reference functions */
#include "sn34f78x_hal_conf.h"

/* Exported functions --------------------------------------------------------*/
/* Initialization/de-initialization functions *********************************/
HAL_Status_T HAL_Init(void);
HAL_Status_T HAL_DeInit(void);

void HAL_MspInit(void);
void HAL_MspDeInit(void);

/* Board pin-mutex initialization functions ***********************************/
void AFIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* _SN34F78X_HAL_H_ */
