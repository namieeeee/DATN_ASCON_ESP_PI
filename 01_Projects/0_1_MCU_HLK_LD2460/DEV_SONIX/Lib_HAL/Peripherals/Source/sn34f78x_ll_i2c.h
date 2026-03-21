/**
 * @file sn34f78x_ll_i2c.h
 * @author PD
 * @brief Private header file of I2C LL driver.
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _SN34F78X_LL_I2C_H_
#define _SN34F78X_LL_I2C_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_ll.h"

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define IS_LL_I2C_INSTANCE(__VALUE__) ((__VALUE__) == SN_I2C0 || \
                                       (__VALUE__) == SN_I2C1 || \
                                       (__VALUE__) == SN_I2C2)
#define IS_LL_I2C_CLOCK_SPEED(__VALUE__)     ((__VALUE__) <= LL_I2C_CLOCKSPEED_HIGH_SPEED)
#define IS_LL_I2C_ADDRESS(__VALUE__)         (((__VALUE__) & ~0x3FF) == 0)
#define IS_LL_I2C_ADDRESSING_MODE(__VALUE__) ((__VALUE__) <= LL_I2C_ADDRESSINGMODE_10BIT)
#define IS_LL_I2C_GC_EN(__VALUE__)           ((__VALUE__) == LL_ENABLE || (__VALUE__) == LL_DISABLE)

/* Private functions prototypes ----------------------------------------------*/

#endif /* _SN34F78X_LL_I2C_H_ */
