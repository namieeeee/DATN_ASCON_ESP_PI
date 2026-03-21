
/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#include "init.h"
#include "../../main_task.h"
#include "../../hlk_ld2460.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>  
/* USER CODE BEGIN #0 */
extern UART_Handle_T UART1_Handle;
extern UART_Handle_T UART2_Handle;
static HLK_CTX hlk;
static volatile uint8_t rx1;
const uint8_t demo[] = { 0xF4,0xF3,0xF2,0xF1,0x04, 0x0F,0x00, 0x0F,0x00,0x17,0x00, 0xF8,0xF7,0xF6,0xF5 };

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

     HLK_Init(&hlk);
		 //HAL_UART_Transmit(&UART1_Handle, (uint8_t*)HLK_EN_REPORT, sizeof(HLK_EN_REPORT), 50);
     U2_Enqueue("CMD: EN_REPORT\r\n", 17);
     U2_Enqueue("BOOT OK\r\n", (uint16_t)strlen("BOOT OK\r\n"));
		 U2_Enqueue("TX-IT ARMED\r\n", (uint16_t)strlen("TX-IT ARMED\r\n"));
			 
					for (size_t i=0;i<sizeof(demo);i++) HLK_FeedByte(&hlk, demo[i]);
					HLK_Report r;
					if (HLK_TryGetReport(&hlk, &r)) {
							print_report_uart2(&r);  // K?t qu?: N=1;P1=(1.5,2.3)
					} else {
							U2_Enqueue("PARSE FAIL\r\n", 12);
					}
     HAL_UART_Receive_IT(&UART1_Handle, (uint8_t*)&rx1, 1);
    while (1)
		{
 
        HLK_Report r;
        if (HLK_TryGetReport(&hlk, &r)) {
            /* Có report m?i -> log sang UART2 (IT) */
            print_report_uart2(&r);
        }
		}
error:
    uninit();
    Error_Handler();
}

void HAL_UART_RxCpltCallback(UART_Handle_T *huart)
{
    if (huart == &UART1_Handle) {
        extern void U2_Enqueue(const char*, uint16_t);
        U2_Enqueue("U1 RXC\r\n", 8);        

        extern HLK_CTX hlk; extern volatile uint8_t rx1;
        HLK_FeedByte(&hlk, (uint8_t)rx1);
        HAL_UART_Receive_IT(&UART1_Handle, (uint8_t*)&rx1, 1);
    }
}



void HAL_UART_TxCpltCallback(UART_Handle_T *huart)
{
    if (huart == &UART2_Handle) {
        u2_tail = (uint8_t)((u2_tail + 1) % U2_Q_LINES);
        u2_busy = 0;
        U2_StartNextIfIdle();
    }
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
    OSCCfg.EHSEn          = RCC_OSCCLK_CFG_OFF; // no Crystal outside -----> OFF
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

