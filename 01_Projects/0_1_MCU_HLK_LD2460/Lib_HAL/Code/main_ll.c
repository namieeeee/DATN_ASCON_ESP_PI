/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */

/* USER CODE END #0 */
int main(void)
{
	/* USER CODE BEGIN #1 */

	/* USER CODE END #1 */

	LL_Init();

	SystemClock_Config();

	if (init() != LL_OK)
		goto error;

	/* USER CODE BEGIN #2 */

	/* USER CODE END #2 */

	while (1)
		;
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
	LL_RCC_OscConfig_t OSCCfg = {0};
	LL_RCC_ClkConfig_t ClkCfg = {0};

	LL_RCC_GetClockConfig(&ClkCfg);
	if (ClkCfg.SYSCLKSource == LL_RCC_SYSCLK_SRC_PLL)
	{
		/* If source of SYSCLK is configured as PLL and want to change any PLL setting(such as NS, FS...) as this time,
			Flash clock frequency should be set large enough in the whole sequence of SYSCLK frequency updating */
		LL_FLASH_Config_ProgramInit_T CfgInit = {
			.option_type = LL_OPTION_CLKFREQ,
			.clk_freq    = 192,
		};
		if (LL_FLASH_ConfigProgram(&CfgInit) != LL_OK)
			Error_Handler();
	}

	OSCCfg.OscillatorType = __OSC_TYPE__;
	OSCCfg.IHRCEn = LL_RCC_OSCCLK_CFG_ON;
__OSC_CONFIG__
	if (LL_RCC_OscConfig(&OSCCfg) != LL_OK)
		Error_Handler();

	ClkCfg.ClockType      = LL_RCC_CLK_TYPE_SYSCLK | LL_RCC_CLK_TYPE_HCLK | LL_RCC_CLK_TYPE_APB0CLK | LL_RCC_CLK_TYPE_APB1CLK;
	ClkCfg.SYSCLKSource   = __RCC_SYSCLK_SRC__;
	ClkCfg.AHBCLKDivider  = LL_RCC_SYSCLK_DIV__RCC_AHB_DIV__;
	ClkCfg.APB0CLKDivider = LL_RCC_HCLK_DIV__RCC_APB1_DIV__;
	ClkCfg.APB1CLKDivider = LL_RCC_SYSCLK_DIV2;
	if (LL_RCC_ClockConfig(&ClkCfg) != LL_OK)
		Error_Handler();

	__CLK_OUT_CLOCK__
}
