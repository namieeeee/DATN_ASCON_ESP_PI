#ifndef __SONIX_APP_H__
#define __SONIX_APP_H__

#include "hal_systick.h"
#include "sn34f78x_hal.h"

extern UART_Handle_T UART0_Handle;
extern UART_Handle_T UART1_Handle;

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
