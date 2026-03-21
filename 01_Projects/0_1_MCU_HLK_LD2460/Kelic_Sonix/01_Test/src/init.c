#include "init.h"

/* USER CODE BEGIN #0 */

/* USER CODE END #0 */
UART_Handle_T UART0_Handle;
UART_Handle_T UART1_Handle;

uint32_t sn34f7_UART0_Init(void)
{
    UART0_Handle.instance         = SN_UART0;
    UART0_Handle.init.baud_rate   = 115200;
    UART0_Handle.init.word_length = UART_WORD_LENGTH_8;
    UART0_Handle.init.stop_bits   = UART_STOP_BITS_1;
    UART0_Handle.init.parity      = UART_PARITY_NONE;
    UART0_Handle.init.hw_flow_ctl = UART_HWCONTROL_NONE;

    if (HAL_OK != HAL_UART_Init(&UART0_Handle))
        return HAL_ERROR;

    return HAL_OK;
}

uint32_t sn34f7_UART1_Init(void)
{
    UART1_Handle.instance         = SN_UART1;
    UART1_Handle.init.baud_rate   = 115200;
    UART1_Handle.init.word_length = UART_WORD_LENGTH_8;
    UART1_Handle.init.stop_bits   = UART_STOP_BITS_1;
    UART1_Handle.init.parity      = UART_PARITY_NONE;
    UART1_Handle.init.hw_flow_ctl = UART_HWCONTROL_NONE;

    if (HAL_OK != HAL_UART_Init(&UART1_Handle))
        return HAL_ERROR;

    return HAL_OK;
}

uint32_t init(void)
{
    /* USER CODE BEGIN Init #0 */

    /* USER CODE END Init #0 */

    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART0_Init(), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART1_Init(), HAL_OK), HAL_ERROR);

    /* USER CODE BEGIN Init #1 */

    /* USER CODE END Init #1 */

    return HAL_OK;
}

uint32_t uninit(void)
{
    /* USER CODE BEGIN Uninit #0 */

    /* USER CODE END Uninit #0 */

    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART0_Handle), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART1_Handle), HAL_OK), HAL_ERROR);

    HAL_DeInit();

    /* USER CODE BEGIN Uninit #1 */

    /* USER CODE END Uninit #1 */

    return HAL_OK;
}
