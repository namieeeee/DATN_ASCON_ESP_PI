/**
* @file       main_task.h
* @version    1.0.0
* @date       2025-10-21
* @author     Tran Nam
*             
* @brief      
*/

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __MAIN_TASK_H
#define __MAIN_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */

#include "hlk_ld2460.h"

/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
	mode_1 = 1,
	mode_2 ,
	mode_3 
} mode_t;

typedef enum
{
	handle_mode_1 = 1,// RUN
	handle_mode_2     // SHUTDOWN
} handle_mode;      
extern volatile uint32_t now;   
extern volatile handle_mode event_handle;

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
extern void main_task(void);
void time_now(void);   
#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif // __MAIN_TASK_H
/* End of file -------------------------------------------------------- */
