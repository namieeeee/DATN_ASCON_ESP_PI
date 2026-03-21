/**
* @file       cbuffer.h
* @version    1.0.0
* @date       2023-12-29
* @author     MinhLCN
*             
* @brief      
*/

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __CBUFFER_H
#define __CBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <string.h>
//#include "common.h"
/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public enumerate/structure ----------------------------------------- */

/*!
 * @brief elements of cbuffer swtruct
 */
 
 typedef enum
{
  R_OK_ = 0,
  R_ERROR_,
  R_NG_,
  R_MAX_,
} ERROR_CODE_T_T;

 
typedef struct
{
    uint8_t *data;
    uint16_t size;
    uint16_t index_write;
    uint16_t index_read;
    uint16_t overflow;
} cbuffer_t;
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/*!
 * @brief  initialize circle buffer
 *
 * @param[in] cb  pointer of cbuffer_t struct
 * @param[in] buf  pointer of array buffer
 * @param[in] size  length of buffer
 *
 */
ERROR_CODE_T_T cbuffer_init(cbuffer_t *cb, void *buf, uint16_t size);
 
/*!
 * @brief  read data from cbuffer and store them into array "buf"
 *
 * @param[in] cb    pointer of cbuffer_t struct
 * @param[in] buf   pointer of array buffer
 * @param[in] bytes  bytes's amount of data
 *
 * @return  
 *  i : byte's amount read from cbuffer
 */
ERROR_CODE_T_T cbuffer_read(cbuffer_t *cb, uint8_t *buf, uint16_t bytes);
 
/*!
 * @brief  write data to buffer
 *
 * @param[in] cb    pointer of cbuffer_t struct
 * @param[in] buf   pointer of array buffer
 * @param[in] bytes  bytes's amount of data
 *
 * @return  
 */
ERROR_CODE_T_T cbuffer_write(cbuffer_t *cb, uint8_t *buf, uint16_t bytes);
 
/*!
 * @brief  return element's value at index but not change read index
 *
 * @param[in] cb    pointer of cbuffer_t struct
 * @param[in] idx   index of array
 *
 * @return  
 *        data : value at index
 */
ERROR_CODE_T_T cbuffer_only_read(cbuffer_t *cb, uint16_t idx, uint8_t *data);
 
/*!
 * @brief  count amount of data in buffer
 *
 * @param[in]  cb   pointer of cbuffer_t struct
 *
 * @return  The number of available data in the circular buffer.
 */
uint16_t cbuffer_data_count(cbuffer_t *cb);
 
/**
 * @brief  Calculates the available space in a circular buffer.
 *
 * @param[in]  cb Pointer to the circular buffer (cbuffer_t structure).
 *
 * @return  The number of available spaces in the circular buffer.
 */
uint16_t cbuffer_space_count(cbuffer_t *cb);
 
/*!
 * @brief   reset a circular buffer
 *
 * @param[in] cb   pointer of cbuffer_t struct
 *
 * @return  The circular buffer was cleared
 */
ERROR_CODE_T_T cbuffer_clear(cbuffer_t *cb);

void Print_cbuffer_debug(cbuffer_t *cb);
#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif // __CBUFFER_H
/* End of file -------------------------------------------------------- */
