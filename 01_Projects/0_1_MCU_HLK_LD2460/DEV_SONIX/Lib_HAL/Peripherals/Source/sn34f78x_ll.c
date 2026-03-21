/**
 * @file sn34f78x_ll.c
 * @author PD
 * @brief   SN34f78x LL initialization file.
 *          This is the common part of the LL initialization.
 * @version 1.0
 * @date 2024-11-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "sn34f78x_ll.h"

// add board information
#include "sn34f78x_board.c"

// add io re-target
#include "retarget_io.c"

/* Exported functions --------------------------------------------------------*/
/*
================================================================================
            ##### Initialization/De-initialization functions #####
================================================================================
*/
/**
 * @brief  This function is used to initialize the LL Library;
 * @note   SysTick is used as time base for the LL_Delay() function, the application
 *         need to ensure that the SysTick time base is always set to 1 millisecond
 *         to have correct LL operation.
 * @retval LL status
 */
LL_Status_T LL_Init(void)
{
    /* Use sys_tick as time base source and configure 1ms tick (default clock after Reset is HSI) */
    LL_InitTick(LL_SYS_TICK_INT_PRIORITY);

    /* Set auto hold and flash operation init */
    LL_InitFlash();

    /* Init the low level hardware */
    LL_MspInit();

#if (defined(EVALUATION_BOARD) || defined(EVALUATION_BOARD_ETH))
    /* Pull reset pin(P3.7) up to high */
    LL_GPIO_Init_T gpio_init = {
        .pin_mask = LL_GPIO_PIN_7,
        .mode     = LL_GPIO_MODE_INPUT,
        .pull     = LL_GPIO_PULL_UP,
        .ie       = LL_DISABLE,
    };
    LL_GPIO_Init(SN_GPIO3, &gpio_init);
    while (!LL_GPIO_IsInputPinSet(SN_GPIO3, LL_GPIO_PIN_7))
    {
        __NOP();
    }
#endif

    /* Return function status */
    return LL_OK;
}
/**
 * @brief  This function de-Initializes common part of the LL and stops the sys_tick.
 *         This function is optional.
 * @retval LL status
 */
LL_Status_T LL_DeInit(void)
{
    /* Reset of all peripherals */

    /* De-Init the low level hardware */
    LL_MspDeInit();

    /* Return function status */
    return LL_OK;
}

/*
================================================================================
            ##### Event Callback functions #####
================================================================================
*/

/**
 * @brief  Initialize the MSP.
 * @retval None
 */
__weak void LL_MspInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed, the LL_MspInit could be implemented in the user file */
}

/**
 * @brief  DeInitializes the MSP.
 * @retval None
 */
__weak void LL_MspDeInit(void)
{
    /* NOTE : This function should not be modified, when the callback is needed,the LL_MspDeInit could be implemented in the user file */
}
