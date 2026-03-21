/**
 * @file sn34f78x_sdk.h
 * @author PD
 * @brief include HAL driver and LL driver
 * @version 1.0
 * @date 2024-11-15
 */

#ifndef _SN34F78X_SDK_H_
#define _SN34F78X_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define configUSE_LL_DRIVER 0
#if (configUSE_LL_DRIVER == 1)
#include "sn34f78x_ll.h"
#endif /* configUSE_LL_DRIVER */

#define configUSE_HAL_DRIVER 0
#if (configUSE_HAL_DRIVER == 1)
#include "sn34f78x_hal.h"
#endif /* configUSE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* _SN34F78X_SDK_H_ */
