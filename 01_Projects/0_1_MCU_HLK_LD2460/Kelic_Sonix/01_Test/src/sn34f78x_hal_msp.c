/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */
// this function is called if an RX interrupt is generated
void HAL_UART_RxCpltCallback(UART_Handle_T *huart)
{
    rx_flag++;
}

// this function is called if an TX interrupt is generated
void HAL_UART_TxCpltCallback(UART_Handle_T *huart)
{
    tx_flag++;
}
/* USER CODE END #0 */

/**
 * The HAL_MspInit will be called in HAL_Init.
 */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit #0 */

	/* USER CODE END MspInit #0 */
}

/**
 * The HAL_MspDeInit will be called in HAL_DeInit.
 */
void HAL_MspDeInit(void)
{
	/* USER CODE BEGIN MspDeInit #0 */

	/* USER CODE END MspDeInit #0 */
}

void HAL_UART_MspInit(UART_Handle_T *huart)
{
	/* USER CODE BEGIN UART_MspInit #0 */

	/* USER CODE END UART_MspInit #0 */

	if (huart->instance == SN_UART0)
	{
		HAL_GPIO_SetAFIO(SN_GPIO3, GPIO_PIN_2, GPIO_P32_UART_URXD0);
		HAL_GPIO_SetAFIO(SN_GPIO3, GPIO_PIN_1, GPIO_P31_UART_UTXD0);

		if (__HAL_RCC_UART0_IS_CLK_DISABLE())
		{
			__HAL_RCC_UART0_CLK_ENABLE();
			__HAL_RCC_UART0_RESET();
		}
		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);
	}

	if (huart->instance == SN_UART1)
	{
		HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_3, GPIO_P23_UART_URXD1);
		HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_2, GPIO_P22_UART_UTXD1);

		if (__HAL_RCC_UART1_IS_CLK_DISABLE())
		{
			__HAL_RCC_UART1_CLK_ENABLE();
			__HAL_RCC_UART1_RESET();
		}
		NVIC_ClearPendingIRQ(UART1_IRQn);
		NVIC_EnableIRQ(UART1_IRQn);
	}


	/* USER CODE BEGIN UART_MspInit #1 */

	/* USER CODE END UART_MspInit #1 */
}
void HAL_UART_MspDeInit(UART_Handle_T *huart){
	/* USER CODE BEGIN UART_MspDeInit #0 */

	/* USER CODE END UART_MspDeInit #0 */

	if (huart->instance == SN_UART0)
	{
		if (__HAL_RCC_UART0_IS_CLK_ENABLE())
		{
			__HAL_RCC_UART0_CLK_DISABLE();
		}

		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_DisableIRQ(UART0_IRQn);

		HAL_GPIO_SetAFIO(SN_GPIO3, GPIO_PIN_2, GPIO_P32_GPIO);
		HAL_GPIO_SetAFIO(SN_GPIO3, GPIO_PIN_1, GPIO_P31_GPIO);

	}

	if (huart->instance == SN_UART1)
	{
		if (__HAL_RCC_UART1_IS_CLK_ENABLE())
		{
			__HAL_RCC_UART1_CLK_DISABLE();
		}

		NVIC_ClearPendingIRQ(UART1_IRQn);
		NVIC_DisableIRQ(UART1_IRQn);

		HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_3, GPIO_P23_GPIO);
		HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_2, GPIO_P22_GPIO);

	}


	/* USER CODE BEGIN UART_MspDeInit #1 */

	/* USER CODE END UART_MspDeInit #1 */
} 

