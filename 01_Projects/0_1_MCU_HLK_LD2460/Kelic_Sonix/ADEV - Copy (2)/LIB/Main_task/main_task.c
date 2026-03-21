/**
* @file       main_task.c
* @version    1.0.0
* @date       2025-10-21
* @author     Tran Nam
* @editor     UTE CHILL GUY
* @brief      
*/

/* Includes ----------------------------------------------------------- */
#include <string.h>
#include <stdint.h>
#include "init.h" 
#include "common.h"
#include "cbuffer.h"
#include "main_task.h"
#include "fpga.h"
#include "hlk_ld2460.h"
#include "System_Management.h"
#include "control_led.h"

/* Private defines ---------------------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */


/* Private variables -------------------------------------------------- */
volatile uint32_t now = 0U;

static uint8_t s_run_at_first         = TRUE_;
static uint8_t s_error_occured        = FALSE_;
static SystemState_t s_state          = STATE_INIT;

/* SENT DATA ESP32/MCU.... */

HLK_CTX radar_ctx;           
volatile uint8_t radar_rx;
volatile uint8_t fpga_rx_byte;
static uint32_t sent_data = 0;

volatile uint8_t btn_flag_1 = 0; // SW2
volatile uint8_t btn_flag_2 = 0; // SW1

static uint8_t peoples                = 0; // 0 : no people 1 : people
static uint8_t peoples_max            = 5;

extern uint8_t shutdown_done;

static mode_t current_mode = mode_1;
volatile  handle_mode event_handle = handle_mode_1;
extern UART_Handle_T UART2_Handle;
//extern handle_mode event_handle;


static uint8_t run_once = 0;
// My code
/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private function definitions --------------------------------------- */
static uint8_t Process_system();
static ERROR_CODE_T s_initialize_peripheral();
static void Process_action(SystemState_t state);
static void execute_action(SystemState_t state);
static void shuttdown_action(void);
static ERROR_CODE_T Process_state_RUN(void);

//static ERROR_CODE_T Deinit_all(void);
//static ERROR_CODE_T s_init_builder(void);
//static void process_interrupt_btn(uint16_t GPIO_Pin);
//static void convert_data_radar(Radar_Data_t data, uint8_t *buf);

/*begin Run mode*/
//void run_mode_1(void);
//void run_mode_2(void);
//void run_mode_3(void);
void mode_event(void);
void RUN_SHUTDOWN_EVENT(void);
void sent_data_uart(void (*callback)(void)) ;
void packet_data_sent(void);
void UART1_StartReceive_IT(void);
void run_mode_1(void) ;
void time_now();
//void main_task();
/* end Run mode */

//static void UART2_Print(const char *msg)
//{
//    HAL_UART_Transmit(&UART3_Handle, (uint8_t*)msg, strlen(msg), 50);
//}
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
        /* ---- STATE_INIT -------------------------------------------------- */
			  case STATE_INIT:
        {
          // HAL_Delay(400);
          s_run_at_first  = TRUE;
          ret             = s_initialize_peripheral();
          UART1_StartReceive_IT();
          //	HAL_Delay(20);
          HLK_Init(&radar_ctx); 
          //FPGA_Init();
            // HAL_UART_Receive_IT(&UART2_Handle, (uint8_t *)&fpga_rx_byte, 1); 					
          /* I will continue to handle this code in the future. */
          if (ret == R_OK)
          {
            (void)Set_event(EVENT_INIT_SUCCESS);
            DEBUG_PRINT_IT("SATE_INIT\r\n");
          }
          else
          {
            (void)Set_event(EVENT_INIT_FAIL);
          }

        }
        break;
        /* ---- STATE_IDLE -------------------------------------------------- */
				case STATE_IDLE:
        {
         // (void)Set_event(EVENT_START_SUCCESS); // test logic
					RUN_SHUTDOWN_EVENT ();
          DEBUG_PRINT_IT("SATE_IDELE\r\n");


        }
        break;
        /* ---- STATE_RUN -------------------------------------------------- */
				case STATE_RUN:
        {
				//	run_mode_1();
					RUN_SHUTDOWN_EVENT();  
					

          mode_event();

          if (run_once == 0)
          {
              DEBUG_PRINT_IT("STATE_RUN\r\n");
              run_once = 1;  
          //  HAL_Delay(400);
          }
        }
        break;
        /* ---- STATE_ERROR -------------------------------------------------- */
				case STATE_ERROR:
        {
        //DEBUG_PRINT_IT("STATE_ERROR\r\n");
          __NVIC_SystemReset(); // Reset

        }
        break;
        /* ---- STATE_SHUTDOWN -------------------------------------------------- */
        case STATE_SHUTDOWN:
        {
					btn_flag_1 = 0;
         // RUN_SHUTDOWN_EVENT();  
          HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12, GPIO_PIN_LOW);
				  HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13, GPIO_PIN_LOW);
          if (!shutdown_done) 
          {
						(void)Set_event(EVENT_SHUTDOWN_SUCCESS);
            shutdown_done = 1;
            DEBUG_PRINT_IT("STATE_SHUTDOWN\r\n");							
          }

        }
        break;
        /* ---------------------------------------------------------------------- */
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

void packet_data_sent(void)
{
	
}


#if 0
void sent_data_uart(void) // 10HZ plese config 100_200ms
{
	int32_t sent_now = HAL_GetTick();
	
  if( sent_now - sent_data > 100 )
  {
    //sent data
    sent_data = sent_now;

  }
	
}
  #endif

void sent_data_uart(void (*callback)(void)) 
{
    //static int32_t sent_data = 0;
    int32_t sent_now = HAL_GetTick();

    if (sent_now - sent_data > 100) 
		{ // 10Hz = 100ms
        sent_data = sent_now;
        if (callback != NULL) {
            callback(); 
        }
    }
}

void time_now()
{
	now = HAL_GetTick();
}
void run_mode_1(void) //RADA HLK LD 2460
{
	
    HLK_Report rpt;
    static uint32_t last_sent = 0;

   
    while (HLK_TryGetReport(&radar_ctx, &rpt))
    {
        if (rpt.num_targets == 0)
            continue;

        peoples = rpt.num_targets;
        if (peoples > peoples_max)
            peoples = peoples_max;


        char out[256];
        int pos = 0;
        pos += snprintf(out + pos, sizeof(out) - pos,
                        "\r\nPeople=%u\r\n", rpt.num_targets);

        for (uint8_t i = 0; i < rpt.num_targets; i++)
        {
            float x = rpt.t[i].x_m;
            float y = rpt.t[i].y_m;

            if (x < -10 || x > 20) x = 0;
            if (y < -10 || y > 20) y = 0;

            pos += snprintf(out + pos, sizeof(out) - pos,
                            "T%u: X=%.2f  Y=%.2f\r\n", i + 1, x, y);
        }
        DEBUG_PRINT_IT(out);
        if (now - last_sent >= 200)
        {
            last_sent = now;

            uint8_t tx_buf[32];
            uint16_t len = 0;

            tx_buf[len++] = 0xAA;             
            tx_buf[len++] = 0x01;            
            tx_buf[len++] = peoples;          
            memcpy(&tx_buf[len], &rpt.t[0].x_m, sizeof(float)); len += 4;
            memcpy(&tx_buf[len], &rpt.t[0].y_m, sizeof(float)); len += 4;
            tx_buf[len++] = 0x0D;
            tx_buf[len++] = 0x0A;


         HAL_UART_Transmit(&UART3_Handle, tx_buf, len, 50);
        }
  
 //sent_data_uart();

     }
}
void run_mode_2(void) // RADA HLK LD 6002
{
  
  //sent_data_uart();

}
void run_mode_3(void)// HLK LD6002 and HLK LD 2460 convert 
{
  //sent_data_uart();

}

void mode_event(void)
{
	    if (Get_state() == STATE_RUN && btn_flag_1)   // ch? d?i khi RUN & c� n�t nh?n
    {
        btn_flag_1 = 0;

        switch (current_mode)
        {
            case mode_1: run_mode_1(); led_mode_1(); break;
            case mode_2: run_mode_2(); led_mode_2(); break;
            case mode_3: run_mode_3(); led_mode_3(); break;
            default: current_mode = mode_1; break;
        }

        current_mode++;
        if (current_mode > mode_3) current_mode = mode_1;
    }
#if 0
	if (Get_state() != STATE_RUN)
	return;

	if (btn_flag_1) 
	{

		btn_flag_1 = 0;

  switch (current_mode)
    {
				case mode_1:
				{
					run_mode_1();
					led_mode_1();
				}
					break;
        case mode_2:
				{
					run_mode_2();
			  	led_mode_2();	
				}
          break;
        case mode_3:
				{
					run_mode_3();
			  	led_mode_3();
				}
          break;
        default:
				{
					current_mode = mode_1;
				}
            break;
    }

		current_mode++;
		if (current_mode  > mode_3) current_mode  = mode_1;

	 }
#endif

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
		//	mode_event();
      event_handle = handle_mode_2; 
			TURN_ON_ALL_LED();
    }
    break;

    case handle_mode_2:
    {
		 (void)Set_event(EVENT_SHUTDOWN_REQUEST);
			btn_flag_1 = 0; 
      event_handle = handle_mode_1;
			TURN_OFF_ALL_LED();
    }
    break;

    default:
      (void)Set_event(EVENT_START_SUCCESS);
      event_handle = handle_mode_1;
    break;
  }
}

static ERROR_CODE_T s_initialize_peripheral()
{
    ERROR_CODE_T ret = R_OK;
    return ret;
}
/*__________________________________END RUN MODE_______________________________________*/

/* Main function  ----------------------------------------------- */

/* End of file -------------------------------------------------------- */

