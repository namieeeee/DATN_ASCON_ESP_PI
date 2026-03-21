/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */

/* USER CODE END #0 */

__irq void SysTick_Handler(void)
{
    /* USER CODE BEGIN SYS_IRQ #0 */

    /* USER CODE END SYS_IRQ #0 */

    HAL_IncTick();

    /* USER CODE BEGIN SYS_IRQ #1 */

    /* USER CODE END SYS_IRQ #1 */
}

__irq void SCU_IRQHandler(void)
{
    /* USER CODE BEGIN SCU_IRQ #0 */

    /* USER CODE END SCU_IRQ #0 */

    HAL_SCU_IRQHandler();

    /* USER CODE BEGIN SCU_IRQ #1 */

    /* USER CODE END SCU_IRQ #1 */
}
/********************* UART ******************************/
__irq void UART0_IRQHandler(void)
{
    /* USER CODE BEGIN UART0_IRQ #0 */

    /* USER CODE END UART0_IRQ #0 */

    HAL_UART_IRQHandler(&UART0_Handle);

    /* USER CODE BEGIN UART0_IRQ #1 */

    /* USER CODE END UART0_IRQ #1 */
}

__irq void UART1_IRQHandler(void)
{
    /* USER CODE BEGIN UART0_IRQ #0 */

    /* USER CODE END UART0_IRQ #0 */

    HAL_UART_IRQHandler(&UART1_Handle);

    /* USER CODE BEGIN UART0_IRQ #1 */

    /* USER CODE END UART0_IRQ #1 */
}

__irq void UART2_IRQHandler(void)
{
    /* USER CODE BEGIN UART0_IRQ #0 */

    /* USER CODE END UART0_IRQ #0 */

    HAL_UART_IRQHandler(&UART2_Handle);

    /* USER CODE BEGIN UART0_IRQ #1 */

    /* USER CODE END UART0_IRQ #1 */
}

__irq void UART3_IRQHandler(void)
{
    /* USER CODE BEGIN UART0_IRQ #0 */

    /* USER CODE END UART0_IRQ #0 */

    HAL_UART_IRQHandler(&UART3_Handle);

    /* USER CODE BEGIN UART0_IRQ #1 */

    /* USER CODE END UART0_IRQ #1 */
}
/** *********************TIMER********************************/
__irq void CT16B0_IRQHandler(void)
{
    /* USER CODE BEGIN TPM_IRQ #0 */

    /* USER CODE END TPM_IRQ #0 */

    HAL_TPM_IRQHandler(&TPM0_Handle);

    /* USER CODE BEGIN TPM_IRQ #1 */

    /* USER CODE END TPM_IRQ #1 */
}
/** *********************GPIO********************************/
__irq void GPIO1_IRQHandler(void)
{
    /* USER CODE BEGIN SCU_IRQ #0 */

    /* USER CODE END SCU_IRQ #0 */

    HAL_GPIO_IRQHandler(SN_GPIO1);

    /* USER CODE BEGIN SCU_IRQ #1 */

    /* USER CODE END SCU_IRQ #1 */
}

__irq void GPIO3_IRQHandler(void)
{
    /* USER CODE BEGIN SCU_IRQ #0 */

    /* USER CODE END SCU_IRQ #0 */

    HAL_GPIO_IRQHandler(SN_GPIO3);

    /* USER CODE BEGIN SCU_IRQ #1 */

    /* USER CODE END SCU_IRQ #1 */
}
