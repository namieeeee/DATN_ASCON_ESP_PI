/**
 * @file sn34f78x_ll_conf.h
 * @author PD
 * @brief enum all peripheries and middlewares driver function.
 * The QS tool will copy current file to generated project
 * The APP project which created by manual should copy current to project.
 *
 * By enable/disable reference IP symbol to use or unused IP driver.
 * @version 1.0
 * @date 2024-11-15
 *
 */
//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef _SN34F78X_LL_CONF_H_
#define _SN34F78X_LL_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

//<o0> Internal resistor of EHS X'TAL control
//       <0=> Enable
//       <1=> Disable
//<o1> EHS Source Frequency (MHz)   <10-25>
//       <i> EHS frequency range = 10 ~ 25
//
#define LL_EHS_INR_DS   0  /**< Internal resistor of EHS X'TAL control */
#define LL_EHS_FREQ_MHZ 12 /**< EHS Source Frequency (MHz) */

#define _EHS_FREQ    (LL_EHS_FREQ_MHZ * 1000000UL) /**< EHS  frequency(HZ) */
#define _IHRC_FREQ   (12000000UL)                  /**< IHRC frequency */
#define LL_ILRC_FREQ (32000UL)                     /**< ILRC frequency */

#define LL_SYS_TICK_INT_PRIORITY 0x0FU /**< tick interrupt priority */
#include "ll_systick.h"
#include "ll_gpio.h"
#include "ll_rcc.h"
#include "ll_scu.h"

// <e> ADC (Analog to Digital Converter)
#define configUSE_ADC_PERIPHERAL_LL 0 /**< 0: Disable ADC driver; 1: Enable ADC driver; default is 0 */
#if (configUSE_ADC_PERIPHERAL_LL == 1)
#include "ll_adc.h"
#endif /* configUSE_ADC_PERIPHERAL_LL */
// </e> ADC (Analog to Digital Converter)

// <e> CRC (Cyclic Redundancy Check)
#define configUSE_CRC_PERIPHERAL_LL 0 /**< 0: Disable CRC driver; 1: Enable CRC driver; default is 0 */
#if (configUSE_CRC_PERIPHERAL_LL == 1)
#include "ll_crc.h"
#endif /* configUSE_CRC_PERIPHERAL_LL */
// </e> CRC (Cyclic Redundancy Check)

// <e> DMA (Direct Memory Access)
#define configUSE_DMA_PERIPHERAL_LL 0 /**< 0: Disable DMA driver; 1: Enable DMA driver; default is 0 */
#if (configUSE_DMA_PERIPHERAL_LL == 1)
#include "ll_dma.h"
#endif /* configUSE_DMA_PERIPHERAL_LL */
// </e> DMA (Direct Memory Access)

// <e> FMC (Flash Memory Controller)
#define configUSE_FLASH_PERIPHERAL_LL 1 /**< 0: Disable Flash driver; 1: Enable Flash driver; default is 1 */
#if (configUSE_FLASH_PERIPHERAL_LL == 1)
#include "ll_flash.h"
#endif /* configUSE_FLASH_PERIPHERAL_LL */
// </e> FMC (Flash Memory Controller)

// <e> I2C (Inter-Integrated Circuit)
#define configUSE_I2C_PERIPHERAL_LL 0 /**< 0: Disable I2C driver; 1: Enable I2C driver; default is 0 */
#if (configUSE_I2C_PERIPHERAL_LL == 1)
#include "ll_i2c.h"
#endif /* configUSE_I2C_PERIPHERAL_LL */
// </e> I2C (Inter-Integrated Circuit)

// <e> IWDG (Independent WatchDog Timer)
#define configUSE_IWDG_PERIPHERAL_LL 0 /**< 0: Disable IWDG driver; 1: Enable IWDG driver; default is 0 */
#if (configUSE_IWDG_PERIPHERAL_LL == 1)
#include "ll_iwdg.h"
#endif /* configUSE_IWDG_PERIPHERAL_LL */
// </e> IWDG (Independent WatchDog Timer)

// <e> PWR (Power Management)
#define configUSE_PWR_PERIPHERAL_LL 0 /**< 0: Disable PWR driver; 1: Enable PWR driver; default is 0 */
#if (configUSE_PWR_PERIPHERAL_LL == 1)
#include "ll_pwr.h"
#endif /* configUSE_PWR_PERIPHERAL_LL */
// </e> PWR (Power Management)

// <e> RTC (Real Time Clock)
#define configUSE_RTC_PERIPHERAL_LL 0 /**< 0: Disable RTC driver; 1: Enable RTC driver; default is 0 */
#if (configUSE_RTC_PERIPHERAL_LL == 1)
#include "ll_rtc.h"
#endif /* configUSE_RTC_PERIPHERAL_LL */
// </e> RTC (Real Time Clock)

// <e> SSP (Synchronous Serial Port)
#define configUSE_SSP_PERIPHERAL_LL 0 /**< 0: Disable SSP driver; 1: Enable SSP driver; default is 0 */
#if (configUSE_SSP_PERIPHERAL_LL == 1)
#include "ll_ssp.h"
#endif /* configUSE_SSP_PERIPHERAL_LL */
// </e> SSP (Synchronous Serial Port)

// <e> TPM (16-BIT Timer with Capture)
#define configUSE_TPM_PERIPHERAL_LL 0 /**< 0: Disable TPM driver; 1: Enable TPM driver; default is 0 */
#if (configUSE_TPM_PERIPHERAL_LL == 1)
#include "ll_tpm0.h"
#include "ll_tpm125.h"
#include "ll_tpm3.h"
#include "ll_tpm4.h"
#include "ll_tpm67.h"
#include "ll_tpm8.h"
#endif /* configUSE_TPM_PERIPHERAL_LL */
// </e> TPM (16-BIT Timer with Capture)

// <e> UART (Universal Asynchronous Receiver and Transmitter)
#define configUSE_UART_PERIPHERAL_LL 0 /**< 0: Disable UART driver; 1: Enable UART driver; default is 0 */
#if (configUSE_UART_PERIPHERAL_LL == 1)
#include "ll_uart0123.h"
#include "ll_uart45.h"
#endif /* configUSE_UART_PERIPHERAL_LL */
// </e> UART (Universal Asynchronous Receiver and Transmitter)

// <e> WWDG (Window WatchDog Timer)
#define configUSE_WWDG_PERIPHERAL_LL 0 /**< 0: Disable WWDG driver; 1: Enable WWDG driver; default is 0 */
#if (configUSE_WWDG_PERIPHERAL_LL == 1)
#include "ll_wwdg.h"
#endif /* configUSE_WWDG_PERIPHERAL_LL */
// </e> WWDG (Window WatchDog Timer)

#ifdef __cplusplus
}
#endif

#endif //_SN34F78X_LL_CONF_H_

//-------- <<< end of configuration section >>> --------------------
