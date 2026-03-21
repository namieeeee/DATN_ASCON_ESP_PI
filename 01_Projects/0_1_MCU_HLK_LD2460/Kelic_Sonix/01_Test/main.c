/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"

/* USER CODE BEGIN #0 */


// define tx/rx finish interrupt callback flag
volatile int8_t tx_flag = 0;
volatile int8_t rx_flag = 0;

// define data
uint8_t data_rx[TRANSFER_CNT] = {0};
uint8_t data_tx[TRANSFER_CNT] = {0};

// initializes the data to be sent
void fill_data(uint8_t *data, uint32_t cnt)
{
    for (uint32_t i = 0; i < cnt; ++i)
    {
        data_tx[i] = i + 1;
    }
}
/**
 * @brief  uart0 tx and uart1 rx.
 * @retval HAL status
 */
HAL_Status_T _uart0_tx_uart1_rx_it_8bit(void)
{
    // prepare data
    fill_data(data_tx, TRANSFER_CNT);
    memset(data_rx, 0, TRANSFER_CNT);

    // Data transmit,UART1 rx receives data from UART0 tx, so pin connection is required
    if (HAL_UART_Receive_IT(&UART1_Handle, data_rx, TRANSFER_CNT) != HAL_OK)
        return HAL_ERROR;
    if (HAL_UART_Transmit_IT(&UART0_Handle, data_tx, TRANSFER_CNT) != HAL_OK)
        return HAL_ERROR;

    // wait for transmission to complete
    while (tx_flag == 0 || rx_flag == 0)
        ;
    rx_flag = 0;
    tx_flag = 0;

    // compare data
    if (memcmp(data_tx, data_rx, TRANSFER_CNT) != 0)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}
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
    //_uart0 tx and uart1 rx.
    if (_uart0_tx_uart1_rx_it_8bit() != HAL_OK)
        goto error;
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
            .CLKFreq    = 192,
        };
        if (HAL_FLASHEx_ConfigProgram(&CfgInit) != HAL_OK)
            Error_Handler();
    }

    OSCCfg.OscillatorType = RCC_OSC_TYPE_IHRC | RCC_OSC_TYPE_EHS;
    OSCCfg.IHRCEn         = RCC_OSCCLK_CFG_ON;
    OSCCfg.EHSEn          = RCC_OSCCLK_CFG_OFF;
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
