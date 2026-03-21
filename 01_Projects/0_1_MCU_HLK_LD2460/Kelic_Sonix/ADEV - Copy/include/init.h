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
