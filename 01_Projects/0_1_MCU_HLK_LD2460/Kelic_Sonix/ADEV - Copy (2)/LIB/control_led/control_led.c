#ifdef __cplusplus
extern "C" {
#endif

#include "control_led.h"
#include "init.h"    

static void green_display();
static void red_display();
static void blue_display();
static void orange_display();
static void control_led(SystemState_t state);

/****************************************************************************************
 *                              INTERNAL FUNCTION (PRIVATE)
 ****************************************************************************************/
	



/****************************************************************************************
 *                              PUBLIC FUNCTION IMPLEMENTATION
 ****************************************************************************************/
/*
TURN_ON_GREEN_LED()   |	  TURN_OFF_GREEN_LED       |    TOGGLE_GREEN_LED
TURN_ON_ORANGE_LED()  |   TURN_OFF_ORANGE_LED      |    TOGGLE_ORANGE_LED
TURN_ON_RED_LED()     |   TURN_OFF_RED_LED         |    TOGGLE_RED_LED
TURN_ON_BLUE_LED()    |   TURN_OFF_BLUE_LED        |    TOGGLE_BLUE_LED
TURN_ON_LED_1()       |   TURN_OFF_LED_1           |    TOGGLE_LED_1
TURN_ON_LED_2()       |   TURN_OFF_LED_2           |    TOGGLE_LED_2

	*/
	//void Led_displays(SystemState_t state)
	//{
	//static uint32_t current_time = 0;

	//current_time = HAL_GetTick();
	//if ((current_time - get_last_time()) >= FREQUENCY)
	//{
	//	set_last_time(current_time);
	//	control_led(state);
	//}
	//}	
static void green_display()
{
	TURN_ON_GREEN_LED();
	TURN_OFF_ORANGE_LED();
	TURN_OFF_RED_LED();
	TURN_OFF_BLUE_LED();
}
static void red_display()
{
	TURN_ON_RED_LED();
	TURN_OFF_ORANGE_LED();
	TURN_OFF_GREEN_LED();
	TURN_OFF_BLUE_LED();
}
static void blue_display()
{
	TURN_ON_BLUE_LED();	
	TURN_OFF_GREEN_LED();
	TURN_OFF_ORANGE_LED();
	TURN_OFF_RED_LED();
}
static void orange_display()
{
	TURN_ON_ORANGE_LED();
	TURN_OFF_GREEN_LED();
	TURN_OFF_RED_LED();
	TURN_OFF_BLUE_LED();
}

void TURN_ON_ALL_LED(void)
{
	TURN_ON_GREEN_LED();
	TURN_ON_ORANGE_LED();
	TURN_ON_RED_LED();
	TURN_ON_BLUE_LED();
}

void TURN_OFF_ALL_LED(void)
{
	TURN_OFF_GREEN_LED();
	TURN_OFF_ORANGE_LED();
	TURN_OFF_RED_LED();
	TURN_OFF_BLUE_LED();
}
void led_mode_1(void)
{
	TURN_ON_LED_1();
	TURN_OFF_LED_2();
}
void led_mode_2(void)
{
	TURN_OFF_LED_1();
	TURN_ON_LED_2();
}
void led_mode_3(void)
{
	TURN_ON_LED_1();
	TURN_ON_LED_2();
}
#if 0
//static LED_Handle leds[] =
//{
//    { SN_GPIO1, GPIO_PIN_12 }, // LED1
//    { SN_GPIO1, GPIO_PIN_13 }, // LED2
//};



//void LED_ON(LED_ID id)
//{
//    HAL_GPIO_WritePin(leds[id].port, leds[id].pin, GPIO_PIN_HIGH);
//}

//void LED_OFF(LED_ID id)
//{
//    HAL_GPIO_WritePin(leds[id].port, leds[id].pin, GPIO_PIN_LOW);
//}

//void LED_Toggle(LED_ID id)
//{
//    HAL_GPIO_TogglePin(leds[id].port, leds[id].pin);
//}

//	

//void led_mode_1(void)
//{
//	LED_ON(LED1);
//	LED_OFF(LED2);
//}
//void led_mode_2(void)
//{
//	LED_OFF(LED1);
//	LED_ON(LED2);
//}
//void led_mode_3(void)
//{
//	LED_ON(LED1);
//	LED_ON(LED2);
//}
#endif

#ifdef __cplusplus
}
#endif
