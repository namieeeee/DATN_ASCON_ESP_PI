/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */
// this function is called if an RX interrupt is generated
void HAL_UART_RxCpltCallback(UART_Handle_T *huart)
{
  //  rx_flag++;
}

// this function is called if an TX interrupt is generated
void HAL_UART_TxCpltCallback(UART_Handle_T *huart)
{
  //  tx_flag++;
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


void HAL_CRC_MspInit(CRC_Handle_T *hcrc)
{
    /* USER CODE BEGIN CRC_MspInit #0 */

    /* USER CODE END CRC_MspInit #0 */
    if (__HAL_RCC_CRC_IS_CLK_DISABLE())
    {
        __HAL_RCC_CRC_CLK_ENABLE();
        __HAL_RCC_CRC_RESET();
    }
    /* USER CODE BEGIN CRC_MspInit #1 */

    /* USER CODE END CRC_MspInit #1 */
}

void HAL_CRC_MspDeInit(CRC_Handle_T *hcrc)
{
    /* USER CODE BEGIN CRC_MspDeInit #0 */

    /* USER CODE END CRC_MspDeInit #0 */

    if (__HAL_RCC_CRC_IS_CLK_ENABLE())
    {
        __HAL_RCC_CRC_CLK_DISABLE();
    }

    /* USER CODE BEGIN CRC_MspDeInit #1 */

    /* USER CODE END CRC_MspDeInit #1 */
}

void HAL_UART_MspInit(UART_Handle_T *huart)
{
	/* USER CODE BEGIN UART_MspInit #0 */

	/* USER CODE BEGIN UART 0                                      */
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
	/* USER CODE END UART 0                                      */
	
	/* USER CODE BEGIN UART 1                                      */
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
	/* USER CODE END UART 1                                      */
	
	/* USER CODE BEGIN UART 2                                    */
		if (huart->instance == SN_UART2)
		{
			HAL_GPIO_SetAFIO(SN_GPIO1, GPIO_PIN_6, GPIO_P16_UART_URXD2);
			HAL_GPIO_SetAFIO(SN_GPIO1, GPIO_PIN_7, GPIO_P17_UART_UTXD2);

			if (__HAL_RCC_UART2_IS_CLK_DISABLE())
			{
				__HAL_RCC_UART2_CLK_ENABLE();
				__HAL_RCC_UART2_RESET();
			}
			NVIC_ClearPendingIRQ(UART2_IRQn);
			NVIC_EnableIRQ(UART2_IRQn);
		}	
	/* USER CODE END UART 2                                      */
	
	/* USER CODE BEGIN UART 3                                    */
			if (huart->instance == SN_UART3)
		{
			HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_1, GPIO_P21_UART_URXD3);
			HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_0, GPIO_P20_UART_UTXD3);

			if (__HAL_RCC_UART3_IS_CLK_DISABLE())
			{
				__HAL_RCC_UART3_CLK_ENABLE();
				__HAL_RCC_UART3_RESET();
			}
			NVIC_ClearPendingIRQ(UART3_IRQn);
			NVIC_EnableIRQ(UART3_IRQn);
		}	
	/* USER CODE END UART 3                                      */
	
	/* USER CODE BEGIN UART 4                                    */
	
	/* USER CODE END UART 4                                      */
	
	/* USER CODE BEGIN UART 5                                    */
	
	/* USER CODE END UART 5                                      */

}
void HAL_UART_MspDeInit(UART_Handle_T *huart)
{
	/* USER CODE BEGIN UART_MspDeInit #0 */

	/* USER CODE END UART_MspDeInit #0 */
	/* USER CODE BEGIN UART 0                                      */
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
	/* USER CODE END UART 0                                      */
	
	/* USER CODE BEGIN UART 1                                      */
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
	/* USER CODE END UART 1                                      */
	
	/* USER CODE BEGIN UART 2                                      */
	    if (huart->instance == SN_UART2)
    {
        if (__HAL_RCC_UART2_IS_CLK_ENABLE())
        {
            __HAL_RCC_UART2_CLK_DISABLE();
        }

        NVIC_ClearPendingIRQ(UART2_IRQn);
        NVIC_DisableIRQ(UART2_IRQn);

        HAL_GPIO_SetAFIO(SN_GPIO1, GPIO_PIN_6, GPIO_P16_GPIO);  // RX2 -> GPIO
        HAL_GPIO_SetAFIO(SN_GPIO1, GPIO_PIN_7, GPIO_P17_GPIO);  // TX2 -> GPIO
        return;
    }
	/* USER CODE END UART 2                                    */
	
	/* USER CODE BEGIN UART 3                                      */
    if (huart->instance == SN_UART3)
    {
        if (__HAL_RCC_UART3_IS_CLK_ENABLE())
        {
            __HAL_RCC_UART3_CLK_DISABLE();
        }

        NVIC_ClearPendingIRQ(UART3_IRQn);
        NVIC_DisableIRQ(UART3_IRQn);

        HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_1, GPIO_P21_GPIO);  // RX3 -> GPIO
        HAL_GPIO_SetAFIO(SN_GPIO2, GPIO_PIN_0, GPIO_P20_GPIO);  // TX3 -> GPIO
        return;
    }	
	/* USER CODE END UART 3                                   */
	



	/* USER CODE BEGIN UART_MspDeInit #1 */

	/* USER CODE END UART_MspDeInit #1 */
} 

