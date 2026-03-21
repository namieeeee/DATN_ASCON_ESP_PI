/*
* @file       System_Management.h
* @version    1.0.0
* @date       2025-03-08
* @author     MinhLCN
*             
* @brief      
*/


/* Includes ----------------------------------------------------------- */
#include "System_Management.h"
#include "init.h" 
#include "main_task.h"
/* Private defines ---------------------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private variables -------------------------------------------------- */
static SystemState_t currentState     = STATE_INIT;
static SystemState_t next_State       = STATE_INIT;
static Event_t s_event                = EVENT_MAX;

volatile uint8_t shutdown_done = 0;  
extern volatile handle_mode event_handle;
/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private function definitions --------------------------------------- */
/* Function definitions ----------------------------------------------- */
void judge_state(void)
{
  switch (currentState)
  {
  case STATE_INIT:
    if (s_event == EVENT_INIT_SUCCESS)
    {
      //SM_PRINT_TRACE("next_State = STATE_IDLE\r\n");
      next_State = STATE_IDLE;
    }
    else if (s_event == EVENT_INIT_FAIL)
    {
   //SM_PRINT_TRACE("next_State = STATE_ERROR\r\n");
      next_State = STATE_ERROR;
    }
    break;

  case STATE_IDLE:
    if (s_event == EVENT_START_SUCCESS)
    {
     // SM_PRINT_TRACE("next_State = STATE_RUN\r\n");
      next_State = STATE_RUN;
    }
    else if (s_event == EVENT_START_FAIL)
    {
     // SM_PRINT_TRACE("next_State = STATE_ERROR\r\n");
      next_State = STATE_ERROR;
    }
    break;
  case STATE_RUN:
    if (s_event == EVENT_SHUTDOWN_REQUEST)
    {
     // SM_PRINT_TRACE("next_State = STATE_SHUTDOWN\r\n");
      next_State = STATE_SHUTDOWN;
    }
    else if (s_event == EVENT_ERROR_OCCUR)
    {
    //  SM_PRINT_TRACE("next_State = STATE_ERROR\r\n");
      next_State = STATE_ERROR;
    }
    break;

  case STATE_SHUTDOWN:
#if 0
    if (s_event == EVENT_SHUTDOWN_SUCCESS)
    {
			shutdown_done = 0;
        event_handle  = handle_mode_1;

        DEBUG_PRINT_IT("Shutdown complete ? back to IDLE\r\n");

    //  SM_PRINT_TRACE("next_State = STATE_STOP\r\n");
      next_State = STATE_STOP;
    }
    else if (s_event == EVENT_SHUTDOWN_FAIL)
    {
     // SM_PRINT_TRACE("next_State = STATE_STOP\r\n");
      next_State = STATE_STOP;
    }
#endif
	    if (s_event == EVENT_SHUTDOWN_SUCCESS)
    {

        shutdown_done = 0;
        event_handle  = handle_mode_1;
				next_State = STATE_IDLE;	
        DEBUG_PRINT_IT("Shutdown complete back to IDLE\r\n");
    }
    else if (s_event == EVENT_SHUTDOWN_FAIL)
    {
        next_State = STATE_ERROR;
    }
		else
    {
        DEBUG_PRINT_IT("STATE_SHUTDOWN: waiting for user confirm\r\n");
			 HAL_Delay(400);
    }
    break;

  case STATE_ERROR:
    if (s_event == EVENT_FORCE_STOP)
    {
     // SM_PRINT_TRACE("Force stop\r\n");
      next_State = STATE_STOP;
    }
    else if (s_event == EVENT_RESET)
    {
     // SM_PRINT_TRACE("Reset\r\n");
      next_State = STATE_INIT;
    }
    break;

  case STATE_STOP:
    /* Do nothing*/
  case STATE_MAX:
  default:
    break;
  }

  /* Update state lasted */
  currentState = next_State;
}

SystemState_t Get_state(void)
{
    return currentState;
}

ERROR_CODE_T Set_event(Event_t event)
{
  ERROR_CODE_T ret = R_OK;

  if (event < EVENT_MAX)
  {
    s_event = event;
  }
  else
  {
    ret = R_ERROR;
  }

  return ret;
}
/* Main function  ----------------------------------------------- */

/* End of file -------------------------------------------------------- */

