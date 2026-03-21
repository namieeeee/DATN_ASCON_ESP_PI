#ifndef __FPGA_H__
#define __FPGA_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float hr;
    float br;
    float dist;
    uint8_t flag;
    uint8_t ready;
} FPGA_Frame_t;

void FPGA_Init(void);
void FPGA_ProcessByte(uint8_t b);
bool FPGA_TryGet(FPGA_Frame_t *out);

extern volatile uint8_t fpga_rx_byte;

#ifdef __cplusplus
}
#endif

#endif

