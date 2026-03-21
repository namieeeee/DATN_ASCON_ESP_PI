/**
* @file       main_task.c
* @version    1.0.0
* @date       2025-10-21
* @author     Tran Nam
* @brief      
*/

/* Includes ----------------------------------------------------------- */
#include "main_task.h"
#include "common.h"
#include "init.h" 
#include "System_Management.h"
#include <string.h>
#include <stdint.h>
#include "cbuffer.h"

/* Private defines ---------------------------------------------------- */
/* Private macros ----------------------------------------------------- */
uint8_t radar_buf_data[1024];
/* Private enumerate/structure ---------------------------------------- */


/* Private variables -------------------------------------------------- */
//static uint8_t number_mode = 1;
static SystemState_t s_state          = STATE_INIT;
static uint8_t s_error_occured        = FALSE_;
static uint8_t s_run_at_first         = TRUE_;

extern uint8_t shutdown_done;
//#define mode_t current_mode = mode_1; 
static uint8_t peoples                = 0; // 0 : no people 1 : people
static uint8_t peoples_max            = 5;
/////////////////////////////////////////////////////////////////////////
static mode_t current_mode = mode_1;
handle_mode event_handle = handle_mode_1;
//extern handle_mode event_handle;

// My code
volatile uint8_t btn_flag_1 = 0;
volatile uint8_t btn_flag_2 = 0;
/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private function definitions --------------------------------------- */

//static ERROR_CODE_T Deinit_all(void);
//static ERROR_CODE_T s_init_builder(void);
//static void process_interrupt_btn(uint16_t GPIO_Pin);
static ERROR_CODE_T s_initialize_peripheral();
static uint8_t Process_system();
static void Process_action(SystemState_t state);
static void execute_action(SystemState_t state);
static void shuttdown_action(void);
static ERROR_CODE_T Process_state_RUN(void);
cbuffer_t cb_radar;
// static void run_mode_1(void);
// static void run_mode_2(void);
// static void run_mode_3(void);
//static void convert_data_radar(Radar_Data_t data, uint8_t *buf);

/*begin Run mode*/
void mode_event(void);
void RUN_SHUTDOWN_EVENT(void);
void Process_incoming_from_radar(void); 
//void main_task();
/* end Run mode */


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
					DEBUG_PRINT_IT("SATE_INIT\r\n");
          HAL_Delay(400);
//					(void)Set_event(EVENT_INIT_SUCCESS);
					 s_run_at_first  = TRUE;
           ret             = s_initialize_peripheral();
           //  ret == R_OK;
            /* I will continue to handle this code in the future. */
            if (ret == R_OK)
            {
						 // 	Streams_Init();
						//	cbuffer_init();
                (void)Set_event(EVENT_INIT_SUCCESS);
            }
            else
            {
                (void)Set_event(EVENT_INIT_FAIL);
						}

        }
        break;
/****************************************************************************************/
				case STATE_IDLE:
        {
				DEBUG_PRINT_IT("SATE_IDELE\r\n");
        HAL_Delay(400);
				RUN_SHUTDOWN_EVENT ();

				//	(void)Set_event(EVENT_START_SUCCESS);
        }
        break;
/****************************************************************************************/
				case STATE_RUN:
        {
				 mode_event();
				//Process_incoming_from_radar();
				 RUN_SHUTDOWN_EVENT();  
			  //DEBUG_PRINT_IT("SATE_RUN\r\n");
				//	 HAL_Delay(400);
        }
        break;
/****************************************************************************************/
				case STATE_ERROR:
        {
        //DEBUG_PRINT_IT("STATE_ERROR\r\n");
        __NVIC_SystemReset(); // Reset
				   //Error_Handler();
        }
        break;
/****************************************************************************************/
        case STATE_SHUTDOWN:
        {
					
					  RUN_SHUTDOWN_EVENT();  
//					 (void)Set_event(EVENT_SHUTDOWN_SUCCESS);
//					//void shuttdown_action(void);
//           DEBUG_PRINT_IT("STATE_SHUTDOWN\r\n");
					  if (!shutdown_done) 
						{
							shutdown_done = 1;
						//	(void)Set_event(EVENT_SHUTDOWN_SUCCESS); 
            //  DEBUG_PRINT_IT("STATE_SHUTDOWN\r\n");							
            }

        }
        break;
/****************************************************************************************/
        case STATE_STOP:
        case STATE_MAX:
        default:
        break;

		}

}


static void shuttdown_action(void)
{
	
}

static ERROR_CODE_T Process_state_RUN(void)
{
  ERROR_CODE_T ret = R_OK;
	return ret;

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

/*__________________________________BEGIN RUN MODE_____________________________________*/
static void run_mode_1(void)
{


}
static void run_mode_2(void)
{
  

}
static void run_mode_3(void)
{
  

}

void mode_event(void)
{
	if (btn_flag_1) 
	{

		btn_flag_1 = 0;

    //HAL_GPIO_TogglePin(SN_GPIO1, GPIO_PIN_12);
        
  switch (current_mode)
    {
        case mode_1:
					run_mode_1();
					HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_HIGH);
				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_LOW);
           // current_mode = mode_2;
            break;

        case mode_2:
					run_mode_2();
					HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_LOW);
				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_HIGH);
           // current_mode = mode_3;
            break;

        case mode_3:
					run_mode_3();
					HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_HIGH);
				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_HIGH);
				 
           // current_mode = mode_1;
          break;

        default:
        current_mode = mode_1;
            break;
    }
		current_mode++;
		if (current_mode  > mode_3) current_mode  = mode_1;
	 }

}
#if 0
void RUN_SHUTDOWN_EVENT (void)
{
		if (btn_flag_2) 
	{

		btn_flag_2 = 0;
    switch(event_handle)
		{
			case handle_mode_1:
			{
//					HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_HIGH);
//				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_LOW);	
			  (void)Set_event(EVENT_START_SUCCESS);
				event_handle = handle_mode_2;
			}
			break;
			case handle_mode_2:
			{
//					HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_LOW);
//				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_HIGH);
				 event_handle = handle_mode_1;
				
			}
			break;
			default:
			(void)Set_event(EVENT_SHUTDOWN_REQUEST);
      event_handle = handle_mode_1;
		}
//		event_handle++;
//		if (event_handle  > handle_mode_2) event_handle  = handle_mode_1;

	 }

}
#endif

void Buffers_Init(void)
{
    cbuffer_init(&cb_radar, radar_buf_data, sizeof(radar_buf_data));
   // cbuffer_init(&cb_esp,  esp_buf_data,  sizeof(esp_buf_data));
}


void RUN_SHUTDOWN_EVENT(void)
{
    if (!btn_flag_2) return;       
    btn_flag_2 = 0;

    switch (event_handle)
    {
        case handle_mode_1:
        {

            (void)Set_event(EVENT_START_SUCCESS);
            event_handle = handle_mode_2; 
        }
        break;

        case handle_mode_2:
        {
           if (Get_state() == STATE_SHUTDOWN)
            {
							 (void)Set_event(EVENT_SHUTDOWN_SUCCESS);
							 event_handle = handle_mode_1;
							 DEBUG_PRINT_IT("Button: EXIT SHUTDOWN ? IDLE\r\n");
            }
            else if (Get_state() == STATE_RUN)
            {
             
							(void)Set_event(EVENT_SHUTDOWN_REQUEST);
               DEBUG_PRINT_IT("Button: RUN ? SHUTDOWN\r\n");
            }
        }
        break;

        default:
            (void)Set_event(EVENT_SHUTDOWN_REQUEST);
            event_handle = handle_mode_1;
            break;
    }
}
static void DEBUG_PRINT_HEX_IT(const uint8_t *data, uint16_t len)
{
#if DEBUG_ENABLE
    if (!data || len == 0) return;

    char line[100];
    uint16_t i = 0;

    while (i < len)
    {
        int n = 0;
        n += snprintf(line + n, sizeof(line) - n, "%04u: ", i);

        for (uint8_t j = 0; j < 16 && i < len; ++j, ++i)
        {
            n += snprintf(line + n, sizeof(line) - n, "%02X ", data[i]);
            if (n >= (int)sizeof(line) - 4) break;
        }

        n += snprintf(line + n, sizeof(line) - n, "\r\n");
        DEBUG_PRINT_IT(line);
    }
#endif
}

static ERROR_CODE_T s_initialize_peripheral()
{
    ERROR_CODE_T ret = R_OK;

//   ret = s_init_builder();
//    if (ret != R_OK)
//    {
//        SM_PRINT_ERROR("Init builder failed\r\n");
//    }
//    else
//    {
//      ret = (ERROR_CODE_T)Radar_init(&huart1);
//      if (ret != R_OK)
//      {
//          SM_PRINT_ERROR("Init Radar failed\r\n");
//      }
//      else
//      {
//          ret = ESP32UART_Init(&huart2);
//          if (ret != R_OK)
//          {
//            SM_PRINT_ERROR("Init ESP32 failed\r\n");
//          }
//          else
//          {
//              ret = SMS_Init(&huart6);
//              if (ret != R_OK)
//              {
//                SM_PRINT_ERROR("Init SMS failed\r\n");
//              }
//          }
//      }
//    }
    return ret;
}

static int cb_peek(cbuffer_t *cb, uint16_t idx, uint8_t *out)
{
    return (cbuffer_only_read(cb, idx, out) == R_OK_) ? 0 : -1;
}

 void Process_incoming_from_radar(void)
{


    while (cbuffer_data_count(&cb_radar) >= 8) // d? t?i thi?u d? soi header/len
    {
        uint8_t b0;
        if (cb_peek(&cb_radar, 0, &b0) != 0) break;

        if (b0 == 0xF4)
        {
            // C?n d? t?i thi?u: 4(header)+1(func)+2(len)+4(tail) = 11 byte
            if (cbuffer_data_count(&cb_radar) < 11) break;

            uint8_t h0,h1,h2,h3, func, len_lo, len_hi;
            cb_peek(&cb_radar, 0, &h0);
            cb_peek(&cb_radar, 1, &h1);
            cb_peek(&cb_radar, 2, &h2);
            cb_peek(&cb_radar, 3, &h3);

            if (h0==0xF4 && h1==0xF3 && h2==0xF2 && h3==0xF1) // header OK :contentReference[oaicite:17]{index=17}
            {
                cb_peek(&cb_radar, 4, &func);
                cb_peek(&cb_radar, 5, &len_lo);
                cb_peek(&cb_radar, 6, &len_hi);
                uint16_t total_len = ((uint16_t)len_hi << 8) | len_lo; // contentReference[oaicite:18]{index=18}

                if (cbuffer_data_count(&cb_radar) < total_len) break; // ch? d? g�i

              
                uint8_t frame_buf[512];
                if (total_len > sizeof(frame_buf)) {
              
                    uint8_t tmp; for (uint16_t i=0;i<total_len;i++) cbuffer_read(&cb_radar,&tmp,1);
                    continue;
                }
                cbuffer_read(&cb_radar, frame_buf, total_len);

                //  F8 F7 F6 F5
                if (!(total_len >= 11 &&
                      frame_buf[total_len-4]==0xF8 && frame_buf[total_len-3]==0xF7 &&
                      frame_buf[total_len-2]==0xF6 && frame_buf[total_len-1]==0xF5)) {
              
                    continue;
                }
#if DEBUG_ENABLE
                DEBUG_PRINTLN_IT("Radar frame received:");
                DEBUG_PRINT_HEX_IT(frame_buf, total_len);
#endif

                if (func == 0x04) {

                }
            }
            else {
           
                uint8_t drop; cbuffer_read(&cb_radar, &drop, 1);
            }
        }
        
        else {
       
            uint8_t drop; cbuffer_read(&cb_radar, &drop, 1);
        }
    }
}

/*__________________________________END RUN MODE_______________________________________*/

/* Main function  ----------------------------------------------- */

/* End of file -------------------------------------------------------- */

