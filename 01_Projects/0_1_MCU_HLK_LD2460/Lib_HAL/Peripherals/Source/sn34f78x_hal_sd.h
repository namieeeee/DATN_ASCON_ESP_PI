/**
 * @file sn34f78x_hal_SD.h
 * @author SW
 * @brief Define the private structure, option for SN34F7 HAL SD.
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _HAL_SN34F7_SD_H_
#define _HAL_SN34F7_SD_H_

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_hal.h"

/* Private macros ------------------------------------------------------------*/
#define IS_PERIPHERAL_SD_INSTANCE(handle, res) \
    if (((handle)->instance) != SN_SDIO)       \
    {                                          \
        return res;                            \
    }

#define SDIO_PRINT(fmt, args...)     printf("[SD1]" fmt "\r", ##args)
#define SDIO_PRINT_ERR(fmt, args...) printf("[SD1](error)" fmt "\r", ##args)

/* Private struct ------------------------------------------------------------*/

typedef struct
{
    uint16_t attr;
    uint16_t lgth;
    uint32_t addr;
} SDIO_Adma2DescTable;

/****************************** SDIO Instances ********************************/
#define IS_SDMMC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == SN_SDIO)

#define IS_SDMMC_CLKDIV(DIV) (((DIV) == SDMMC_INIT_CLK_DIV) ||     \
                              ((DIV) == SDMMC_TRANSFER_CLK_DIV) || \
                              ((DIV) == SDMMC_HIGH_TRANSFER_CLK_DIV))

#define IS_SDMMC_BUS_WIDE(WIDE) (((WIDE) == SDMMC_BUS_WIDE_1B) || \
                                 ((WIDE) == SDMMC_BUS_WIDE_4B) || \
                                 ((WIDE) == SDMMC_BUS_WIDE_8B))

#define SDMMC_ERASE_MAX_BLK_CNT (4 * 1024 * 1024) // Unit: block(512B)

#endif /* _HAL_SN34F7_SD_H_ */
