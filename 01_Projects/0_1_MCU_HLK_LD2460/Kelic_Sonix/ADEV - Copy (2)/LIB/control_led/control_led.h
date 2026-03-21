#ifndef __CONTROL_LED_H
#define __CONTROL_LED_H

#ifdef __cplusplus
extern "C" {
#endif  

#include <stdint.h>
#include <stdbool.h>
#include "init.h"
#include "System_Management.h"
/*----------------TURN_ON_LED-------------------------------------------------------------------------*/
#define TURN_ON_GREEN_LED()    do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_8  , GPIO_PIN_LOW);}while(0)
#define TURN_ON_ORANGE_LED()   do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_9  , GPIO_PIN_LOW);}while(0)
#define TURN_ON_RED_LED()      do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_10 , GPIO_PIN_LOW);}while(0)
#define TURN_ON_BLUE_LED()     do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_11 , GPIO_PIN_LOW);}while(0)
#define TURN_ON_LED_1()        do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12 , GPIO_PIN_LOW);}while(0)
#define TURN_ON_LED_2()        do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13 , GPIO_PIN_LOW);}while(0)
/*----------------TURN_OFF_LED------------------------------------------------------------------------*/
#define TURN_OFF_GREEN_LED()   do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_8  , GPIO_PIN_HIGH);}while(0)
#define TURN_OFF_ORANGE_LED()  do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_9  , GPIO_PIN_HIGH);}while(0)
#define TURN_OFF_RED_LED()     do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_10 , GPIO_PIN_HIGH);}while(0)
#define TURN_OFF_BLUE_LED()    do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_11 , GPIO_PIN_HIGH);}while(0)
#define TURN_OFF_LED_1()       do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_12 , GPIO_PIN_HIGH);}while(0)
#define TURN_OFF_LED_2()       do {HAL_GPIO_WritePin(SN_GPIO1, GPIO_PIN_13 , GPIO_PIN_HIGH);}while(0)
/*-----------------TOGGLE_LED------------------------------------------------------------------------------*/
#define TOGGLE_GREEN_LED()     do {HAL_GPIO_TogglePin(SN_GPIO1 , GPIO_PIN_8 );}while(0)
#define TOGGLE_ORANGE_LED()    do {HAL_GPIO_TogglePin(SN_GPIO1 , GPIO_PIN_9 );}while(0)
#define TOGGLE_RED_LED()       do {HAL_GPIO_TogglePin(SN_GPIO1 , GPIO_PIN_10);}while(0)
#define TOGGLE_BLUE_LED()    	 do {HAL_GPIO_TogglePin(SN_GPIO1 , GPIO_PIN_11);}while(0)
#define TOGGLE_LED_1()         do {HAL_GPIO_TogglePin(SN_GPIO1, GPIO_PIN_12);}while(0)
#define TOGGLE_LED_2()         do {HAL_GPIO_TogglePin(SN_GPIO1, GPIO_PIN_13);}while(0)

#define FREQUENCY                     200U

/****************************************************************************************
 *                              CONFIGURATION SECTION
 ****************************************************************************************/
//typedef enum
//{
//    LED1 = 0,
//    LED2 = 1,
//} LED_ID;

//typedef struct
//{
//    SN_GPIO_Type port;
//    uint32_t pin;
//} LED_Handle;

/****************************************************************************************
 *                              DATA STRUCTURES
 ****************************************************************************************/


/****************************************************************************************
 *                              PUBLIC FUNCTION APIs
 ****************************************************************************************/
//void LED_Init(void);
//void LED_ON(LED_ID id);
//void LED_OFF(LED_ID id);
//void LED_Toggle(LED_ID id);
void led_mode_1(void);
void led_mode_2(void);
void led_mode_3(void);
void led_state_idle(void);
void led_state_run(void);
void TURN_ON_ALL_LED(void);
void TURN_OFF_ALL_LED(void);

#ifdef __cplusplus
}
#endif

#endif /* __MY_LIBRARY_H */
