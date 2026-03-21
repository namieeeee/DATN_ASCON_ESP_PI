#include "init.h"

/* USER CODE BEGIN #0 */
UART_Handle_T UART0_Handle;
UART_Handle_T UART1_Handle;
UART_Handle_T UART2_Handle;
UART_Handle_T UART3_Handle;

CRC_Handle_T CRC_Handle;


/* USER CODE END #0 */


TPM_Handle_T TPM0_Handle;

uint32_t sn34f7_TPM0_Init(void)
{
    TPM0_Handle.instance        = SN_CT16B0;
    TPM0_Handle.init.pre_scaler = 191;
    TPM0_Handle.init.mode       = TPM_CTM_TIMER;
    TPM0_Handle.init.cm         = TPM_COUNTING_UP;

    if (HAL_TPM_Init(&TPM0_Handle) != HAL_OK)
        return HAL_ERROR;

    TPM_OC_T TPM0_CH0_CFG = {0};
    TPM0_CH0_CFG.mode     = TPM_OCMODE_TIMER;
    TPM0_CH0_CFG.period   = 200;
    TPM0_CH0_CFG.reset    = HAL_DISABLE;
    TPM0_CH0_CFG.stop     = HAL_DISABLE;

    if (HAL_TPM_OC_ConfigChannel(&TPM0_Handle, &TPM0_CH0_CFG, TPM_CHANNEL_0) != HAL_OK)
        return HAL_ERROR;

    TPM_OC_T TPM0_CH1_CFG = {0};
    TPM0_CH1_CFG.mode     = TPM_OCMODE_TIMER;
    TPM0_CH1_CFG.period   = 200;
    TPM0_CH1_CFG.reset    = HAL_DISABLE;
    TPM0_CH1_CFG.stop     = HAL_DISABLE;

    if (HAL_TPM_OC_ConfigChannel(&TPM0_Handle, &TPM0_CH1_CFG, TPM_CHANNEL_1) != HAL_OK)
        return HAL_ERROR;

    TPM_OC_T TPM0_CH9_CFG = {0};
    TPM0_CH9_CFG.mode     = TPM_OCMODE_TIMER;
    TPM0_CH9_CFG.period   = 2000;
    TPM0_CH9_CFG.reset    = HAL_ENABLE;
    TPM0_CH9_CFG.stop     = HAL_DISABLE;

    if (HAL_TPM_OC_ConfigChannel(&TPM0_Handle, &TPM0_CH9_CFG, TPM_CHANNEL_9) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}


uint32_t sn34f7_CRC_Init(void)
{
    CRC_Handle.instance        = SN_CRC;
    CRC_Handle.init.polynomial = CRC_POLY_CRC_16_CCITT;
    if (HAL_OK != HAL_CRC_Init(&CRC_Handle))
        return HAL_ERROR;
    return HAL_OK;
}

/*      Config UART 0         */
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

/*      Config UART 1         */

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

/*      Config UART 2         */

uint32_t sn34f7_UART2_Init(void)
{
    UART2_Handle.instance         = SN_UART2;
    UART2_Handle.init.baud_rate   = 115200;
    UART2_Handle.init.word_length = UART_WORD_LENGTH_8;
    UART2_Handle.init.stop_bits   = UART_STOP_BITS_1;
    UART2_Handle.init.parity      = UART_PARITY_NONE;
    UART2_Handle.init.hw_flow_ctl = UART_HWCONTROL_NONE;

    if (HAL_OK != HAL_UART_Init(&UART2_Handle))
        return HAL_ERROR;

    return HAL_OK;
}

/*      Config UART 3         */
uint32_t sn34f7_UART3_Init(void)
{
    UART3_Handle.instance         = SN_UART3;
    UART3_Handle.init.baud_rate   = 115200;
    UART3_Handle.init.word_length = UART_WORD_LENGTH_8;
    UART3_Handle.init.stop_bits   = UART_STOP_BITS_1;
    UART3_Handle.init.parity      = UART_PARITY_NONE;
    UART3_Handle.init.hw_flow_ctl = UART_HWCONTROL_NONE;

    if (HAL_OK != HAL_UART_Init(&UART3_Handle))
        return HAL_ERROR;

    return HAL_OK;
}


uint32_t init(void)
{
    /* USER CODE BEGIN Init #0 */

    /* USER CODE END Init #0 */
    
	/*   CRC CRC CRC */
	  RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_CRC_Init(), HAL_OK), HAL_ERROR);
	
	// UART UART UART UART UART UART UART 
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART0_Init(), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART1_Init(), HAL_OK), HAL_ERROR);
		RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART2_Init(), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART3_Init(), HAL_OK), HAL_ERROR);
	
	//TIMER TIMER TIMER TIMER TIMER TIMER 
	  RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_TPM0_Init(), HAL_OK), HAL_ERROR);

    /* USER CODE BEGIN Init #1 */

    /* USER CODE END Init #1 */

    return HAL_OK;
}

uint32_t uninit(void)
{
    /* USER CODE BEGIN Uninit #0 */

    /* USER CODE END Uninit #0 */
	
	  RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_CRC_DeInit(&CRC_Handle), HAL_OK), HAL_ERROR);

    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART0_Handle), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART1_Handle), HAL_OK), HAL_ERROR);
	  RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART2_Handle), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART3_Handle), HAL_OK), HAL_ERROR);
	
	
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_TPM_DeInit(&TPM0_Handle), HAL_OK), HAL_ERROR);
    HAL_DeInit();

    /* USER CODE BEGIN Uninit #1 */

    /* USER CODE END Uninit #1 */

    return HAL_OK;
}
