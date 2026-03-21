#ifndef __SONIX_APP_H__
#define __SONIX_APP_H__

#include "hal_systick.h"
#include "sn34f78x_hal.h"

extern TPM_Handle_T TPM0_Handle;

extern UART_Handle_T UART0_Handle;
extern UART_Handle_T UART1_Handle;
extern UART_Handle_T UART2_Handle;
extern UART_Handle_T UART3_Handle;

#define RADAR_UART   (&UART1_Handle)
#define LOG_UART     (&UART2_Handle)


uint32_t init(void);
uint32_t uninit(void);
void     Error_Handler(void);
void     SystemClock_Config(void);
/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#endif //__SONIX_APP_H__
