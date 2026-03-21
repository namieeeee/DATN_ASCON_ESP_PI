#include "fpga.h"
#include "init.h"
#include <string.h>

#define SOF  0x5A
#define LEN  14
#define CMD  0xA1

enum {
    F_WAIT_SOF,
    F_WAIT_LEN,
    F_WAIT_CMD,
    F_WAIT_DATA,
    F_WAIT_CS
};

static uint8_t state = F_WAIT_SOF;
static uint8_t buf[32];
static uint8_t idx = 0;
static uint8_t checksum = 0;

static FPGA_Frame_t last_frame;

void FPGA_Init(void)
{
    state = F_WAIT_SOF;
    idx = 0;
    checksum = 0;
    last_frame.ready = 0;
}

void FPGA_ProcessByte(uint8_t b)
{
    switch(state)
    {
        case F_WAIT_SOF:
            if (b == SOF)
            {
                checksum = 0;
                idx = 0;
                state = F_WAIT_LEN;
            }
            break;

        case F_WAIT_LEN:
            if (b == LEN) 
            {
                checksum ^= b;
                state = F_WAIT_CMD;
            }
            else 
            {
                state = F_WAIT_SOF;
            }
            break;

        case F_WAIT_CMD:
            if (b == CMD) 
            {
                buf[0] = b;
                checksum ^= b;
                idx = 1;
                state = F_WAIT_DATA;
            }
            else 
            {
                state = F_WAIT_SOF;
            }
            break;

        case F_WAIT_DATA:
            buf[idx++] = b;
            checksum ^= b;

            if (idx >= LEN)
                state = F_WAIT_CS;
            break;

        case F_WAIT_CS:
        {
            if (checksum == b)
            {
                uint32_t raw_hr   = (buf[1]<<24)|(buf[2]<<16)|(buf[3]<<8)|buf[4];
                uint32_t raw_br   = (buf[5]<<24)|(buf[6]<<16)|(buf[7]<<8)|buf[8];
                uint32_t raw_dist = (buf[9]<<24)|(buf[10]<<16)|(buf[11]<<8)|buf[12];
                uint8_t  flag     = buf[13];

                memcpy(&last_frame.hr,   &raw_hr,   4);
                memcpy(&last_frame.br,   &raw_br,   4);
                memcpy(&last_frame.dist, &raw_dist, 4);
                last_frame.flag = flag;

                last_frame.ready = 1;
            }

            state = F_WAIT_SOF;
            idx = 0;
        }
        break;
    }
}

bool FPGA_TryGet(FPGA_Frame_t *out)
{
    if (!last_frame.ready)
        return false;

    *out = last_frame;
    last_frame.ready = 0;
    return true;
}
