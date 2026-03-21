/**
 * @file SN34F78X_LL_IWDG.h
 * @author PD
 * @brief Private header file of IWDG LL driver.
 * @version 1.0
 * @date 2023-03-1
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SN34F78X_LL_IWDG_H_
#define SN34F78X_LL_IWDG_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_ll.h"

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define IS_LL_IWDG_LOAD(__VALUE__) ((__VALUE__ >= LL_IWDG_TIMER_MIN) && (__VALUE__ <= LL_IWDG_TIMER_MAX))

/* Private functions prototypes ----------------------------------------------*/

#endif /* SN34F78X_LL_IWDG_H_ */
