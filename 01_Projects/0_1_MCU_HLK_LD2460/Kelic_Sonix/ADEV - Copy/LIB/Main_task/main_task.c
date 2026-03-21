/**
* @file       main_task.c
* @version    1.0.0
* @date       
* @author     Tran Nam
* @brief      
*/

/* Includes ----------------------------------------------------------- */
#include "main_task.h"
#include "common.h"
#include "init.h" 
#include "System_Management.h"
/* Private defines ---------------------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */


/* Private variables -------------------------------------------------- */
static SystemState_t s_state          = STATE_INIT;
static uint8_t s_error_occured        = FALSE;
// My code


/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private function definitions --------------------------------------- */
static uint8_t Process_system();
//static ERROR_CODE_T Deinit_all(void);
//static ERROR_CODE_T s_initialize_peripheral();
//static ERROR_CODE_T s_init_builder(void);
//static void process_interrupt_btn(uint16_t GPIO_Pin);
static void Process_action(SystemState_t state);
static void execute_action(SystemState_t state);
static ERROR_CODE_T Process_state_RUN(void);
//static void convert_data_radar(Radar_Data_t data, uint8_t *buf);
/* Function definitions ----------------------------------------------- */
void main_task()
{
    /* Get state to execute action */
      s_state = Get_state();

    /* Execute action */
      Process_action(s_state);

    /* Update state*/
     judge_state();
}


static void execute_action(SystemState_t state)
{
    ERROR_CODE_T ret = R_OK;

    switch (state)
    {
/****************************************************************************************/
			  case STATE_INIT:
        {

        }
        break;
/****************************************************************************************/
				case STATE_IDLE:
        {

        }
        break;
/****************************************************************************************/
				case STATE_RUN:
        {

        }
        break;
/****************************************************************************************/
				case STATE_ERROR:
        {

        }
        break;
/****************************************************************************************/
        case STATE_SHUTDOWN:
        {
        

        }
        break;
/****************************************************************************************/
        case STATE_STOP:
        case STATE_MAX:
        default:
        break;

		}

}
static ERROR_CODE_T Process_state_RUN(void)
{
  ERROR_CODE_T ret = R_OK;

}
static void Process_action(SystemState_t state)
{
    /* Execute action flow the state */
    execute_action(state);

    /* Led display flow the state */
    //Led_displays(state);
}
static uint8_t Process_system()
{

    return s_error_occured;
}
/* Main function  ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
