#include "stm32f4xx.h"
#include <stdio.h>

// Định nghĩa các trạng thái
typedef enum
{
    STATE_INIT,
    STATE_IDLE,
    STATE_RUN,
    STATE_ERROR,
    STATE_SHUTDOWN,
    STATE_STOP
} SystemState_t;

SystemState_t currentState = STATE_INIT;
int reset_count = 0;

void StateMachine_Run(void)
{
    switch (currentState)
    {
    case STATE_INIT:
        printf("INIT State\n");
        if (Initialization_Success())
        {
            currentState = STATE_IDLE;
        }
        else
        {
            currentState = STATE_ERROR;
        }
        break;

    case STATE_IDLE:
        printf("IDLE State\n");
        if (Request_Start())
        {
            currentState = STATE_RUN;
        }
        else if (Start_Fail())
        {
            currentState = STATE_ERROR;
        }
        break;

    case STATE_RUN:
        printf("RUN State\n");
        if (Occur_Error())
        {
            currentState = STATE_ERROR;
        }
        else if (Request_Shutdown())
        {
            currentState = STATE_SHUTDOWN;
        }
        break;

    case STATE_ERROR:
        printf("ERROR State\n");
        if (reset_count > 3)
        {
            currentState = STATE_STOP;
        }
        else
        {
            reset_count++;
            currentState = STATE_INIT;
        }
        break;

    case STATE_SHUTDOWN:
        printf("SHUTDOWN State\n");
        if (Shutdown_Success())
        {
            currentState = STATE_STOP;
        }
        else
        {
            currentState = STATE_ERROR;
        }
        break;

    case STATE_STOP:
        printf("STOP State\n");
        break;
    }
}

// Giả lập các hàm điều kiện bool
int Initialization_Success() { return 1; }
int Request_Start() { return 0; }
int Start_Fail() { return 0; }
int Occur_Error() { return 0; }
int Request_Shutdown() { return 0; }
int Shutdown_Success() { return 1; }

int main()
{
    while (currentState != STATE_STOP)
    {
        StateMachine_Run();
    }
    printf("System Stopped.\n");
    return 0;
}
