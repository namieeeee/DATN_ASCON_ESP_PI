
/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

/* Standard C library headers */

/* Project-specific headers */
#include "init.h"     
#include "main_task.h"


//#include "control_led.h"
/* USER CODE BEGIN #0 */


/* USER CODE END #0 */
int main(void)
{
    /* USER CODE BEGIN #1 */

    /* USER CODE END #1 */

    HAL_Init();

    SystemClock_Config();

    if (init() != HAL_OK)
        goto error;
     
		
    /* USER CODE BEGIN #2 */
   
    /* USER CODE END #2 */


    while (1)
    {
		//	TURN_ON_ALL_LED();
        main_task();
    }

error:
    uninit();
    Error_Handler();
}

void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}
void SystemClock_Config(void)
{
    RCC_OscConfig_t OSCCfg = {0};
    RCC_ClkConfig_t ClkCfg = {0};

    HAL_RCC_GetClockConfig(&ClkCfg);
    if (ClkCfg.SYSCLKSource == RCC_SYSCLK_SRC_PLL)
    {
        /* If source of SYSCLK is configured as PLL and want to change any PLL setting(such as NS, FS...) as this time,
           Flash clock frequency should be set large enough in the whole sequence of SYSCLK frequency updating */
        FLASH_ConfigProgramInitTypeDef CfgInit = 
        {
            .OptionType = OPTIONCFG_CLKFREQ,
            .CLKFreq    = 192,
        };
        if (HAL_FLASHEx_ConfigProgram(&CfgInit) != HAL_OK)
            Error_Handler();
    }

    OSCCfg.OscillatorType = RCC_OSC_TYPE_IHRC | RCC_OSC_TYPE_EHS;
    OSCCfg.IHRCEn         = RCC_OSCCLK_CFG_ON;
    OSCCfg.EHSEn          = RCC_OSCCLK_CFG_OFF; // no Crystal outside -----> OFF plese do not delete
    OSCCfg.PLL.PLLEn      = RCC_OSCCLK_CFG_ON;
    OSCCfg.PLL.PLLSource  = RCC_PLL_SRC_IHRC;
    OSCCfg.PLL.NS         = 64;
    OSCCfg.PLL.FS         = RCC_PLL_DIV4;
    if (HAL_RCC_OscConfig(&OSCCfg) != HAL_OK)
        Error_Handler();

    ClkCfg.ClockType      = RCC_CLK_TYPE_SYSCLK | RCC_CLK_TYPE_HCLK | RCC_CLK_TYPE_APB0CLK | RCC_CLK_TYPE_APB1CLK;
    ClkCfg.SYSCLKSource   = RCC_SYSCLK_SRC_PLL;
    ClkCfg.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    ClkCfg.APB0CLKDivider = RCC_SYSCLK_DIV4;
    ClkCfg.APB1CLKDivider = RCC_SYSCLK_DIV2;
    if (HAL_RCC_ClockConfig(&ClkCfg) != HAL_OK)
        Error_Handler();
}
