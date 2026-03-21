/* --------------------------------------------------------------------------
 * Copyright (c) 2013-2016 Arm Limited ( or its affiliates). All
     * rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  * $Date:        2022-05-18
  * $Revision:    V1.00
  *
  * Project:      First Version
  * -------------------------------------------------------------------------- */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_SYSTEM_H
#define __RTE_SYSTEM_H


//-------------------------------------
    // <h>      Clock Settings
    //-------------------------------------
    // <o0.0> Use External Crystal (12MHz)
    // <i> Use External Crystal(12MHz) as the system clock
    
    // <o1> CPU Clock
    //    <96=> Default: 96 Mhz
    //    <12=>  12 Mhz
    // <i> CONFIG_CPU_CLOCK_MHZ Default: 96Mhz

    
    // <o2> System Clock Divider        <0 =>   /1
    //                                  <1 =>   /2
    //                                  <2 =>   /4
    //                                  <3 =>   /8
    //                                  <4 =>   /16
    //                                  <5 =>   /32
    //                                  <6 =>   /64
    //                                  <7 =>   /128
    // <i> CONFIG_CLK_PRECSALAR Default: 1
   
    // <h> Peripheral Clock Enable setting
    //    <o3.0> CLK Enable - Timer/PWM
    //    <o4.0> CLK Enable - WDT
    //    <o5.0> CLK Enable - I2C
    //    <o6.0> CLK Enable - I2S
    //    <o7.0> CLK Enable - IDMA
    //    <o8.0> CLK Enable - GPIO
    //    <o9.0> CLK Enable - SD1
    //    <o10.0> CLK Enable - UART
    //    <o11.0> CLK Enable - USBD
    //    <o12.0> CLK Enable - SPI
    //    <o13.0> CLK Enable - SPIDMA
    //    <o14.0> CLK Enable - I-Cache
    //    <o15.0> CLK Enable - SAR-ADC
    //    <o16.0> CLK Enable - MCLK_OUT
    //    <o17.0> CLK Enable - Core1
    //    <o18.0> CLK Enable - CRC
    //    <o19.0> CLK Enable - AES
    
    //    <o21.0> CLK Enable - FIR/FFT
    //    <o22.0> CLK Enable - FTDMA
    // </h>

    // </h>     End of Clock Setting

    #define CONFIG_USE_EXTERNAL_CLK         __USE_EXTERNAL_CLK__
    #define CONFIG_CPU_CLOCK_MHZ_SRC        __CPU_CLOCK_MHZ_SRC__
    #define CONFIG_CLK_PRESCALAR            __CLK_PRESCALAR__

    #define CONFIG_PWM_CLK                  __CONFIG_PWM_CLK__
    #define CONFIG_WDT_CLK                  __CONFIG_WDT_CLK__
    #define CONFIG_I2C_CLK                  __CONFIG_I2C_CLK__
    #define CONFIG_I2S_CLK                  __CONFIG_I2S_CLK__
    #define CONFIG_IDMA_CLK                 __CONFIG_IDMA_CLK__
    #define CONFIG_GPIO_CLK                 __CONFIG_GPIO_CLK__
    #define CONFIG_SD1_CLK                  __CONFIG_SD1_CLK__
    #define CONFIG_UART_CLK                 __CONFIG_UART_CLK__
    #define CONFIG_USBD_CLK                 __CONFIG_USBD_CLK__
    #define CONFIG_SPI_CLK                  __CONFIG_SPI_CLK__
    #define CONFIG_SPIDMA_CLK               __CONFIG_SPIDMA_CLK__
    #define CONFIG_ICACHE_CLK               __CONFIG_ICACHE_CLK__
    #define CONFIG_ADC_CLK                  __CONFIG_ADC_CLK__
    #define CONFIG_MCLK_OUT_CLK             __CONFIG_MCLK_OUT_CLK__
    #define CONFIG_CORE1_CLK                __CONFIG_CORE1_CLK__
    #define CONFIG_CRC_CLK                  __CONFIG_CRC_CLK__
    #define CONFIG_AES_CLK                  __CONFIG_AES_CLK__
    #define CONFIG_SPIFC_CLK                1
    #define CONFIG_FFT_CLK                  __CONFIG_FFT_CLK__
    #define CONFIG_FTDMA_CLK                __CONFIG_FTDMA_CLK__
    #define CONFIG_PCLK_SETTING             CONFIG_PWM_CLK | (CONFIG_WDT_CLK << 1) | (CONFIG_I2C_CLK << 2) | (CONFIG_I2S_CLK << 3) | (CONFIG_IDMA_CLK << 4) |                               \
                                            (CONFIG_GPIO_CLK << 5) | (CONFIG_SD1_CLK << 6) | (CONFIG_UART_CLK << 7) | (CONFIG_USBD_CLK << 8) | (CONFIG_SPI_CLK << 9) |                      \
                                            (CONFIG_SPIDMA_CLK << 10) | (CONFIG_ICACHE_CLK << 11) | (CONFIG_ADC_CLK << 12) | (CONFIG_MCLK_OUT_CLK << 14) | (CONFIG_CORE1_CLK << 15) |       \
                                            (CONFIG_CRC_CLK << 16) | (CONFIG_AES_CLK << 17) | (CONFIG_SPIFC_CLK << 18) | (CONFIG_FFT_CLK << 19) | (CONFIG_FTDMA_CLK << 20)

    #define CONFIG_SYS_DEFAULT_FREQ         (CONFIG_CPU_CLOCK_MHZ_SRC * 1000000 / (1 << CONFIG_CLK_PRESCALAR))

#endif /* __RTE_SYSTEM_H*/
