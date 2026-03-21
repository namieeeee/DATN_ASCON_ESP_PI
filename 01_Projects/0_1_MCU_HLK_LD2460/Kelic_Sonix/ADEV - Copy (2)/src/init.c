#include "init.h"

/* USER CODE BEGIN #0 */
UART_Handle_T UART0_Handle; // DEBUG
UART_Handle_T UART1_Handle;
UART_Handle_T UART2_Handle;
UART_Handle_T UART3_Handle;

/****LED_1,  LED_2**/
GPIO_Init_T GPIO1_PIN12_INIT;
GPIO_Init_T GPIO1_PIN13_INIT;
/**  Button MODE and Button Shutdown **/
GPIO_Init_T GPIO1_PIN14_INIT; //MODE
GPIO_Init_T GPIO1_PIN15_INIT; //Shutdown

/*        LED STATE                  */
GPIO_Init_T GPIO1_PIN11_INIT; 
GPIO_Init_T GPIO1_PIN10_INIT;
GPIO_Init_T GPIO1_PIN9_INIT;
GPIO_Init_T GPIO1_PIN8_INIT;


GPIO_Init_T GPIO3_PIN7_INIT;
CRC_Handle_T CRC_Handle;


/* USER CODE END #0 */
uint32_t sn34f7_GPIO_Init(void)
{
/********************************************************************************/
			GPIO3_PIN7_INIT.pin   = GPIO_PIN_7;
			GPIO3_PIN7_INIT.mode  = GPIO_MODE_INPUT;
			GPIO3_PIN7_INIT.pull = GPIO_PULL_UP;
			if (HAL_OK != HAL_GPIO_Init(SN_GPIO3, &GPIO3_PIN7_INIT))
					return HAL_ERROR;
///********************************************************************************/
//    GPIO3_PIN4_INIT.pin  = GPIO_PIN_4;
//    GPIO3_PIN4_INIT.mode = GPIO_MODE_IT_RISING;
//    GPIO3_PIN4_INIT.pull = GPIO_PULL_INACTIVE;

//    if (HAL_OK != HAL_GPIO_Init(SN_GPIO3, &GPIO3_PIN4_INIT))
//        return HAL_ERROR;
/********************GPIO_PIN_8************************************************************/
    GPIO1_PIN8_INIT.pin   = GPIO_PIN_8;
    GPIO1_PIN8_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN8_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN8_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_8, GPIO_PIN_HIGH) != HAL_OK)
        return HAL_ERROR;
/********************GPIO_PIN_9************************************************************/
    GPIO1_PIN9_INIT.pin   = GPIO_PIN_9;
    GPIO1_PIN9_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN9_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN9_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_9, GPIO_PIN_HIGH) != HAL_OK)
        return HAL_ERROR;
/********************GPIO_PIN_10************************************************************/
    GPIO1_PIN10_INIT.pin   = GPIO_PIN_10;
    GPIO1_PIN10_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN10_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN10_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_10, GPIO_PIN_HIGH) != HAL_OK)
        return HAL_ERROR;
/*********************GPIO_PIN_11***********************************************************/
    GPIO1_PIN11_INIT.pin   = GPIO_PIN_11;
    GPIO1_PIN11_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN11_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN11_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_11, GPIO_PIN_HIGH) != HAL_OK)
        return HAL_ERROR;
/**********************GPIO_PIN_12**********************************************************/
    GPIO1_PIN12_INIT.pin   = GPIO_PIN_12;
    GPIO1_PIN12_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN12_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN12_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_LOW) != HAL_OK)
        return HAL_ERROR;
/********************************GPIO_PIN_13************************************************/
    GPIO1_PIN13_INIT.pin   = GPIO_PIN_13;
    GPIO1_PIN13_INIT.mode  = GPIO_MODE_OUTPUT;
    GPIO1_PIN13_INIT.drive = GPIO_DRV_17mA;

    if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN13_INIT))
        return HAL_ERROR;

    if (HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_LOW) != HAL_OK)
        return HAL_ERROR;

/********************************************************************************/
			GPIO1_PIN14_INIT.pin   = GPIO_PIN_14;
			GPIO1_PIN14_INIT.mode  = GPIO_MODE_IT_FALLING;
			GPIO1_PIN14_INIT.pull  = GPIO_PULL_UP;

			if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN14_INIT))
					return HAL_ERROR;
		  HAL_GPIO_ConfigDebounce(SN_GPIO1, GPIO_PIN_14, 1, 10000);
/********************************************************************************/
			GPIO1_PIN15_INIT.pin   = GPIO_PIN_15;
			GPIO1_PIN15_INIT.mode  = GPIO_MODE_IT_FALLING;
			GPIO1_PIN15_INIT.pull  = GPIO_PULL_UP;

			if (HAL_OK != HAL_GPIO_Init(SN_GPIO1, &GPIO1_PIN15_INIT))
					return HAL_ERROR;
		  HAL_GPIO_ConfigDebounce(SN_GPIO1, GPIO_PIN_15, 1, 10000);
			NVIC_ClearPendingIRQ(P1_IRQn);
			NVIC_SetPriority(P1_IRQn, 1);
			NVIC_EnableIRQ(P1_IRQn);

    return HAL_OK;
}

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

/* ============================================================
 *  System Initialization and De-initialization Functions
 *  Sequence guide:
 *    INIT:   Clock --> Core modules --> Peripherals --> GPIO --> App
 *    UNINIT: App --> GPIO --> Peripherals --> Core modules --> Clock
 * ============================================================ */
uint32_t init(void)
{
    /* USER CODE BEGIN Init #0 */
    /* 0) Perform any early user initialization here (before peripherals). */
    /* USER CODE END Init #0 */

    /* 1) Initialize core modules (CRC, power, etc...) */

	  RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_CRC_Init(), HAL_OK), HAL_ERROR);

    /* 2) Initialize communication peripherals ...(UART0–UART3) */	
 
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART0_Init(), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART1_Init(), HAL_OK), HAL_ERROR);
	  RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART2_Init(), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_UART3_Init(), HAL_OK), HAL_ERROR);
	
    /* 3) Initialize timers or PWM modules (TPM0, etc...) */

    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_TPM0_Init(), HAL_OK), HAL_ERROR);
    
    /* 4) Initialize GPIOs for LEDs, buttons, etc. */
    
    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_GPIO_Init(), HAL_OK), HAL_ERROR);

    /* USER CODE BEGIN Init #1 */

    /* USER CODE END Init #1 */

    return HAL_OK;
}

/* ============================================================
 *  System Initialization and De-initialization Functions
 *  Sequence guide:
 *    INIT:   Clock --> Core modules --> Peripherals --> GPIO --> App
 *    UNINIT: App --> GPIO --> Peripherals --> Core modules --> Clock
 * ============================================================ */

uint32_t uninit(void)
{
    /* USER CODE BEGIN Uninit #0 */
    /* 0) Stop application tasks or timers before deinitializing hardware. */
    /* USER CODE END Uninit #0 */

    /* 1) Set GPIOs to a safe state (turn off LEDs, release outputs). */

    RET_FLAG_FALSE(HAL_FLAG_EQU(sn34f7_GPIO_Init(), HAL_OK), HAL_ERROR);

    /* 2) De-initialize communication peripherals (UART0–UART3). */

    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART0_Handle), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART1_Handle), HAL_OK), HAL_ERROR);
	  RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART2_Handle), HAL_OK), HAL_ERROR);
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_UART_DeInit(&UART3_Handle), HAL_OK), HAL_ERROR);

    /* 3) De-initialize timers or other peripherals. */


    /* 4) De-initialize GPIOs (return pins to default floating state).*/
    
    RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_TPM_DeInit(&TPM0_Handle), HAL_OK), HAL_ERROR);

    /* 5) De-initialize core modules (CRC, etc.) */

	  RET_FLAG_FALSE(HAL_FLAG_EQU(HAL_CRC_DeInit(&CRC_Handle), HAL_OK), HAL_ERROR);

    /* 6) Finally shut down the HAL and system clocks.*/


    /* USER CODE BEGIN Uninit #1 */


    /* 7) Optional: User cleanup after hardware is released. */


    /* USER CODE END Uninit #1 */

	

    HAL_DeInit();
	// GPIO GPIO GPIO GPIO GPIO GPIO GPIO 
    /* USER CODE BEGIN Uninit #1 */

    /* USER CODE END Uninit #1 */

    return HAL_OK;
}
