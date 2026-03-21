/**
 * @file hal_sn34f7_systick.h
 * @author PD
 * @brief Define the private structure, option for SN34F7 HAL SysTick.
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _HAL_SN34F7_LCM_H_
#define _HAL_SN34F7_LCM_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_hal.h"

/* Private types -------------------------------------------------------------*/
extern uint32_t SystemCoreClock;
/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
#define IS_TICK_FREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ) ||  \
                            ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                            ((FREQ) == HAL_TICK_FREQ_1KHZ))
/* Private functions prototypes ----------------------------------------------*/

#endif /* _HAL_SN34F7_SYSTICK_H_ */
