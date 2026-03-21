#ifndef __SONIX_APP_H__
#define __SONIX_APP_H__

#include "hal_systick.h"
#include "sn34f78x_hal.h"


#define RADAR_UART   (&UART1_Handle)
#define LOG_UART     (&UART2_Handle)

/* USER CODE BEGIN UART                                   */

extern UART_Handle_T UART0_Handle;
extern UART_Handle_T UART1_Handle;
extern UART_Handle_T UART2_Handle;
extern UART_Handle_T UART3_Handle;
/* USER CODE END UART                                   */



/* USER CODE BEGIN GPIO                                  */

extern GPIO_Init_T GPIO3_PIN7_INIT;
/***********LED****************************************/
extern GPIO_Init_T GPIO1_PIN12_INIT;
extern GPIO_Init_T GPIO1_PIN13_INIT;
/***********BUTTON****************************************/
extern GPIO_Init_T GPIO1_PIN14_INIT; // MODE
extern GPIO_Init_T GPIO1_PIN15_INIT; //shuttdown
/***********LED STATE****************************************/
extern GPIO_Init_T GPIO1_PIN11_INIT; 
extern GPIO_Init_T GPIO1_PIN10_INIT;
extern GPIO_Init_T GPIO1_PIN9_INIT;
extern GPIO_Init_T GPIO1_PIN8_INIT;

/* USER CODE END GPIO                                   */

extern CRC_Handle_T CRC_Handle;

/*   TIME 0 16 BIT */
extern TPM_Handle_T TPM0_Handle;

/*System  plese detele */
uint32_t init(void);
uint32_t uninit(void);
void     Error_Handler(void);
void     SystemClock_Config(void);
/* USER INC & DEF BEGIN */
#define TRANSFER_CNT 128

extern uint8_t         data_tx[TRANSFER_CNT];
extern uint8_t         data_rx[TRANSFER_CNT];
extern volatile int8_t tx_flag;
extern volatile int8_t rx_flag;
/* USER INC & DEF END */

#endif //__SONIX_APP_H__
