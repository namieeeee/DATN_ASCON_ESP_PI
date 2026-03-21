/**
 * @file SN34F78X_LL_WWDG.c
 * @author PD
 * @brief Implementation file of IDWG LL driver.
 * @version 1.0
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "sn34f78x_ll_wwdg.h"

#if defined(USE_FULL_LL_DRIVER)

/* Exported functions --------------------------------------------------------*/
LL_Status_T LL_WWDG_Init(SN_WWDT_Type *wwdg, LL_WWDG_Init_T *wwdg_init)
{
    LL_Status_T status = LL_OK;

    /* Check the parameters */
    RET_FLAG_FALSE(IS_LL_WWDG_LOAD(wwdg_init->counter), LL_ERROR);
    RET_FLAG_FALSE(IS_LL_WWDG_PRESCALER(wwdg_init->prescaler), LL_ERROR);

    /* Delay to wait for the clock to be ready */
    uint32_t sys_clk = LL_RCC_GetHCLKFreq();
    for (uint32_t cnt = 0; cnt < sys_clk / 100000; cnt++)
    {
        __NOP();
    }

    /* enable access to the WWDT_PRESCALER and WWDT_RELOAD */
    LL_WWDG_EnableWriteAccess(wwdg);

    /* set WWDG prescaler*/
    LL_WWDG_SetPrescaler(wwdg, wwdg_init->prescaler);

    /* wait for settings prescaler to complete */
    while (LL_WWDG_IsActiveFlag_PrescalerLock(wwdg) == 0x1)
    {
        __NOP();
    }

    /* Set load value*/
    LL_WWDG_SetReloadCounter(wwdg, wwdg_init->counter);

    /* wait for settings prescaler to complete */
    while (LL_WWDG_IsActiveFlag_ReloadLock(wwdg) == 0x1)
    {
        __NOP();
    }

    /* Set mode*/
    if (wwdg_init->underflow_en == LL_ENABLE)
    {
        RET_FLAG_FALSE(IS_LL_WWDG_WIN_CONSTANT_LESS_TIMER_CONSTANT(wwdg_init->window, wwdg_init->counter), LL_ERROR);
        LL_WWDG_SetWindow(wwdg, wwdg_init->window);
        LL_WWDG_EnableIT_UDF(wwdg);
        LL_WWDG_Enable_UDF(wwdg);
    }
    if (wwdg_init->overflow_en == LL_ENABLE)
    {
        LL_WWDG_EnableIT_OVF(wwdg);
    }
    if (wwdg_init->reset_en == LL_ENABLE)
    {
        LL_WWDG_Enable_Reset(wwdg);
    }

    LL_WWDG_DisableWriteAccess(wwdg);
    /* wait for settings prescaler to complete */
    while (LL_WWDG_IsActiveFlag_ReloadLock(wwdg) == 0x1)
    {
        __NOP();
    }

    LL_WWDG_Start(wwdg);

    /* wait for settings prescaler to complete */
    while (LL_WWDG_IsActiveFlag_ReloadLock(wwdg) == 0x1)
    {
        __NOP();
    }

    return status;
}

LL_Status_T LL_WWDG_DeInit(SN_WWDT_Type *wwdg)
{
    LL_Status_T status = LL_OK;
    /* Disable WWDG */

    return status;
}

void LL_WWDG_StructInit(LL_WWDG_Init_T *wwdg_init)
{
    if (wwdg_init != NULL)
    {
        wwdg_init->prescaler    = LL_WWDG_PRESCALER_7;
        wwdg_init->counter      = LL_WWDG_TIMER_MAX;
        wwdg_init->window       = LL_WWDG_TIMER_MIN;
        wwdg_init->underflow_en = LL_DISABLE;
        wwdg_init->reset_en     = LL_DISABLE;
        wwdg_init->overflow_en  = LL_DISABLE;
    }
}

#endif /* USE_FULL_LL_DRIVER */
