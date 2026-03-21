/**
 * @file sn34f7_hal_assert.h
 * @author PD
 * @brief The AssertParaFalse function is used to check the valid of any function parameters.
 *        if configUSE_ASSERT set to 0, the check action will be disabled.
 *        if configUSE_ASSERT set to 1, the check action will be enabled.
 *        The  modify of configUSE_ASSERT should be in sn34f7_hal_conf.h under user project.
 *
 * @version 1.0
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _SN34F7_HAL_ASSERT_H_
#define _SN34F7_HAL_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_hal_def.h"

/* Exported functions --------------------------------------------------------*/

/* Assert Parameter functions  ********************************/
void AssertParaFalse(uint8_t *file, uint32_t line);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SN34F7_HAL_ASSERT_H_ */
