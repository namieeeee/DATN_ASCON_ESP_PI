/**
 * @file ll_crc.h
 * @author PD
 * @brief
 * @version 1.0
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _LL_CRC_H_
#define _LL_CRC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "sn34f78x_ll_def.h"
#include "ll_reg_msk.h"

/* Exported types ------------------------------------------------------------*/
/**
 * @brief CRC Init structure definition
 * \ingroup crc_struct_define
 */
typedef struct
{
    uint32_t polynomial; /* Specifies the CRC calculation polynomial value.
                            This parameter can be a value of @ref crc_polynomial */
} LL_CRC_Init_T;

/* Exported constants --------------------------------------------------------*/
/**
 * \defgroup crc_polynomial CRC Polynomial
 * \ingroup crc_control
 * @{
 */
#define LL_CRC_POLY_CRC_16_CCITT CRC_CTRL_POLY_CRC_16_CCITT /**< CRC Polynomial CRC-16-CCITT */
#define LL_CRC_POLY_CRC_16       CRC_CTRL_POLY_CRC_16       /**< CRC Polynomial CRC-16 */
#define LL_CRC_POLY_CRC_32       CRC_CTRL_POLY_CRC_32       /**< CRC Polynomial CRC-32 */
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Set the CRC polynomial.
 * @param  crc CRC Instance
 * @param  poly This parameter can be one of @ref crc_polynomial
 * @retval None
 */
__STATIC_INLINE void LL_CRC_SetPoly(SN_CRC_Type *crc, uint32_t poly)
{
    LL_REG_CBIT(crc->CTRL, CRC_CTRL_POLY);
    LL_REG_SBIT(crc->CTRL, poly);
}

/**
 * @brief  Return the CRC polynomial.
 * @param  crc CRC Instance
 * @retval CRC Polynomial, \ref crc_polynomial
 */
__STATIC_INLINE uint32_t LL_CRC_GetPoly(SN_CRC_Type *crc)
{
    return LL_REG_RBIT(crc->CTRL, CRC_CTRL_POLY);
}

/**
 * @brief  Write given 32-bit data to the CRC calculator.
 * @param  crc CRC Instance
 * @param  data value to be provided to CRC calculator between 0 and 0xFFFFFFFF
 * @retval None
 */
__STATIC_INLINE void LL_CRC_FeedData32(SN_CRC_Type *crc, uint32_t data)
{
    LL_REG_WRITE(crc->DATA, data);
}

/**
 * @brief  Return current CRC calculation result. 32 bits value is returned.
 * @param  crc CRC Instance
 * @retval Current CRC calculation result as stored in CRC_Data register (32 bits).
 */
__STATIC_INLINE uint32_t LL_CRC_ReadData32(SN_CRC_Type *crc)
{
    return LL_REG_READ(crc->DATA);
}

/**
 * @brief  Reset the initial seed value and BUSY bit to 0.
 * @param  crc CRC Instance
 * @retval None
 */
__STATIC_INLINE void LL_CRC_Reset(SN_CRC_Type *crc)
{
    LL_REG_SBIT(crc->CTRL, CRC_CTRL_RESET);
}

/**
 * @brief  Return if CRC reset is done.
 * @param  crc CRC Instance
 * @retval State of bit (1 or 0).
 */
__STATIC_INLINE uint32_t LL_CRC_IsResetDone(SN_CRC_Type *crc)
{
    return !(LL_REG_RBIT(crc->CTRL, CRC_CTRL_RESET) == (CRC_CTRL_RESET));
}

/**
 * @brief  Return if CRC calculation is busy.
 * @param  crc CRC Instance
 * @retval State of bit (1 or 0).
 */
__STATIC_INLINE uint32_t LL_CRC_IsBusy(SN_CRC_Type *crc)
{
    return (LL_REG_RBIT(crc->CTRL, CRC_CTRL_BUSY) == (CRC_CTRL_BUSY));
}

#if defined(USE_FULL_LL_DRIVER)
LL_Status_T LL_CRC_Init(SN_CRC_Type *crc, LL_CRC_Init_T *crc_init);
LL_Status_T LL_CRC_DeInit(SN_CRC_Type *crc);
void        LL_CRC_StructInit(LL_CRC_Init_T *crc_init);
#endif /* USE_FULL_LL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LL_CRC_H_ */
