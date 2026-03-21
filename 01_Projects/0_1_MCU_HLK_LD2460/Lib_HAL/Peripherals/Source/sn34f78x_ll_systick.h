/**
 * @file SN34F78X_LL_SYSTICK.h
 * @author PD
 * @brief Private header file of SYSTICK LL driver.
 * @version 1.0
 * @date 2024-11-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SN34F78X_LL_SYSTICK_H_
#define SN34F78X_LL_SYSTICK_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_ll.h"

/* Private types -------------------------------------------------------------*/
extern uint32_t SystemCoreClock;
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define IS_LL_TICK_FREQ(FREQ) (((FREQ) == LL_TICK_FREQ_10HZ) ||  \
                               ((FREQ) == LL_TICK_FREQ_100HZ) || \
                               ((FREQ) == LL_TICK_FREQ_1KHZ))

/* Private functions prototypes ----------------------------------------------*/

#endif /* SN34F78X_LL_SYSTICK_H_ */
