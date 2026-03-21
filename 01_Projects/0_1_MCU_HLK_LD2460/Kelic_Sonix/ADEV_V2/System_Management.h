/**
* @file       System_Management.h
* @version    1.0.0
* @date       2025-03-08
* @author     MinhLCN
*             
* @brief      
*/

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYSTEM_MANAGEMENT_H
#define __SYSTEM_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */

#include "common.h"
/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */
#define MAX_RESET_COUNT     3
#define CHECK_INTERVAL      10
#define MAX_PHONE_NUMBERS   1
#define DEBOUNCE_TIME       50

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  STATE_INIT = 0,
  STATE_IDLE,
  STATE_RUN,
  STATE_ERROR,
  STATE_SHUTDOWN,
  STATE_STOP,
  STATE_MAX
} SystemState_t;

typedef enum
{
  EVENT_INIT_SUCCESS = 0,
  EVENT_INIT_FAIL,
  EVENT_START_SUCCESS,
  EVENT_START_FAIL,
  EVENT_ERROR_OCCUR,
  EVENT_SHUTDOWN_REQUEST,
  EVENT_SHUTDOWN_FAIL,
  EVENT_SHUTDOWN_SUCCESS,
  EVENT_RESET,
  EVENT_FORCE_STOP,
  EVENT_MAX
} Event_t;

/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
extern void judge_state(void);
extern SystemState_t Get_state(void);
extern ERROR_CODE_T Set_event(Event_t event);

#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif // __SYSTEM_MANAGEMENT_H
/* End of file -------------------------------------------------------- */
