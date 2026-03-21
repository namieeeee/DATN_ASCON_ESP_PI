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

#ifndef __RTE_MEMORY_H
#define __RTE_MEMORY_H

// SNC7330 not use currently.
//#define CONFIG_CHIP_PACKAGE         0

//-------------------------------------
// <h>      Flash Settings
//-------------------------------------
// <e> Enable SPI NOR-Flash
// <i> Snc7320 need storage to boot up from reset status.
// <i> Please insert other storage if disabled this item.

#define CONFIG_USE_SPI_FLASH __USE_SPI_FLASH__
#if (CONFIG_USE_SPI_FLASH)

// <o> SPI Flash Clock
//    <1    => AHB_CLK/2
//    <2    => AHB_CLK/4
//    <3    => AHB_CLK/8 (Default)
// <i> SPI Flash Clock Default: AHB_CLK/8
#define CONFIG_FLASH_DIV 3

// <o.0..31> SPI Flash Size
//    <0x80000  => 512KB
//    <0x100000 => 1MB
//    <0x200000 => 2MB
//    <0x400000 => 4MB
//    <0x800000 => 8MB (Default)
//    <0x1000000=> 16MB
// <i> CONFIG_FLASH_SIZE Default: 0x00800000 (hex)
#define CONFIG_FLASH_SIZE 0x00800000

#endif
// </e>
// </h>     End of Flash Setting

//-------------------------------------
// <h>      I-Cache Settings
//-------------------------------------
// <e0.0> Enable I-Cache
// <i> Enable/Disable I-Cache

//     <o1> I-Cache Size      <0x000000=> Auto
//                            <0x100000=> 1M Byte (Max)
//                            <0x0E0000=> 869K Byte
//                            <0x0C0000=> 768K Byte
//                            <0x0A0000=> 640K Byte
//                            <0x080000=> 512K Byte (Default)
//                            <0x060000=> 384K Byte
//                            <0x040000=> 256K Byte
//                            <0x020000=> 128K Byte (Min)
//     <i> The Maximun size of I-Cache region.
//     <i> I-Cache with DRAM takes more time to initialize with bigger cache size.
//
#define CONFIG_USE_ICACHE __USE_ICACHE__

#if (CONFIG_USE_ICACHE)
#define CONFIG_CACHE_SIZE 0x080000
#define CONFIG_CACHE_DEVICE CACHE_DEV_FLASH
#define CONFIG_SIZE_EXT_CODE CONFIG_CACHE_SIZE
#else
#define CONFIG_SIZE_EXT_CODE 0x080000
#endif

#define CONFIG_BASE_LOAD_EXT 0x60011000

// </e>
// </h> End of I-Cache setting

#endif /* __RTE_MEMORY_H */
