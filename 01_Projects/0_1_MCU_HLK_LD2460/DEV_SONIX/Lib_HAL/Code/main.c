/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

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
	RCC_OscConfig_t OSCCfg = {0};
	RCC_ClkConfig_t ClkCfg = {0};

	HAL_RCC_GetClockConfig(&ClkCfg);
	if (ClkCfg.SYSCLKSource == RCC_SYSCLK_SRC_PLL)
	{
		/* If source of SYSCLK is configured as PLL and want to change any PLL setting(such as NS, FS...) as this time,
		   Flash clock frequency should be set large enough in the whole sequence of SYSCLK frequency updating */
		FLASH_ConfigProgramInitTypeDef CfgInit = {
			.OptionType = OPTIONCFG_CLKFREQ,
			.CLKFreq = 192,
		};
		if (HAL_FLASHEx_ConfigProgram(&CfgInit) != HAL_OK)
			Error_Handler();
	}

	OSCCfg.OscillatorType = __OSC_TYPE__;
	OSCCfg.IHRCEn = RCC_OSCCLK_CFG_ON;
__OSC_CONFIG__
	if (HAL_RCC_OscConfig(&OSCCfg) != HAL_OK)
		Error_Handler();

	ClkCfg.ClockType = RCC_CLK_TYPE_SYSCLK | RCC_CLK_TYPE_HCLK | RCC_CLK_TYPE_APB0CLK | RCC_CLK_TYPE_APB1CLK;
	ClkCfg.SYSCLKSource = __RCC_SYSCLK_SRC__;
	ClkCfg.AHBCLKDivider = RCC_SYSCLK_DIV__RCC_AHB_DIV__;
	ClkCfg.APB0CLKDivider = RCC_HCLK_DIV__RCC_APB0_DIV__;
	ClkCfg.APB1CLKDivider = RCC_HCLK_DIV__RCC_APB1_DIV__;
	if (HAL_RCC_ClockConfig(&ClkCfg) != HAL_OK)
		Error_Handler();

	__CLK_OUT_CLOCK__
}
