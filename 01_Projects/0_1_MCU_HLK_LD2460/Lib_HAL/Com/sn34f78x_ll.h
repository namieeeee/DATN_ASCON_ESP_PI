/**
 * @file sn34f78x_ll.h
 * @author PD
 * @brief define the public information for SN34F78x LL SDK
 * @version 1.0
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _SN34F78X_LL_H_
#define _SN34F78X_LL_H_

#ifdef __cplusplus
extern "C" {
#endif

/** board AFIO setting */
#include "sn34f78x_board.h"

/** sn34f78x_ll_conf.h MUST be supplied in project to enable the peripheral reference functions */
#include "sn34f78x_ll_conf.h"

/* Initialization/de-initialization functions *********************************/
LL_Status_T LL_Init(void);
LL_Status_T LL_DeInit(void);

void LL_MspInit(void);
void LL_MspDeInit(void);

/* Board pin-mutex initialization functions ***********************************/
void AFIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* _SN34F78X_LL_H_ */
