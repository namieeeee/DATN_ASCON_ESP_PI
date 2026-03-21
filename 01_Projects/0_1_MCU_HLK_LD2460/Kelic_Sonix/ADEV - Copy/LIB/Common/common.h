/***********************************************************************
* @file       common.h
* @version    1.0.0
* @date       2025-10-21
* @author     Tran Nam
*             
* @brief      
************************************************************************/

#ifndef __COMMON_H
#define __COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include "init.h"


#define DEBUG_ENABLE     1  // 1: ON  ; 0 : OFF
#define DEBUG_UART       UART0_Handle  
#define DEBUG_BUFFER_SIZE   128U

static char buf[DEBUG_BUFFER_SIZE];  
static char *debug_ptr = buf;       

extern UART_Handle_T     UART0_Handle;
//extern UART_Handle_T     UART1_Handle;
//extern UART_Handle_T     UART2_Handle;
//extern UART_Handle_T     UART3_Handle;

/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */
#define ON                  1U
#define OFF                 0U
#define TRUE_               1U
#define FALSE_              0U
#define HIGH                1U
#define LOW                 0U
#define PRESS               0U
#define RELEASE             1U



/* BEGIN Public enumerate/structure ----------------------------------------- */
typedef enum
{
  R_OK = 0,
  R_ERROR,
  R_NG,
  R_MAX,
} ERROR_CODE_T;


/* END Public enumerate/structure ----------------------------------------- */


/*!
 * @brief  This function returns a 32-bit unsigned integer
 *         representing the system time in milliseconds.
 *
 * @return  
 *  The function returns the current system time
 *  in milliseconds as a uint32_t value.
 *!
 */
//extern uint32_t get_tick_ms();



/*USER CONFIG DMA/IT */
static inline void DEBUG_PRINT_IT(const char *s)
{
#if DEBUG_ENABLE
    if (s && *s)
    {
        HAL_UART_Transmit_IT(&DEBUG_UART, (uint8_t*)s, strlen(s));
    }
#endif
}


static inline void DEBUG_PRINTLN_IT(const char *s)
{
#if DEBUG_ENABLE
    uint16_t len = snprintf(buf, sizeof(buf), "%s\r\n", s);
    HAL_UART_Transmit_IT(&DEBUG_UART, (uint8_t*)buf, len);
#endif
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif// __COMMON_H

/* End of file -------------------------------------------------------- */
