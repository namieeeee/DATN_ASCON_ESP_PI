
/***********************************************************************
* @file       hlk_ld2460.h
* @version    1.0.0
* @date       2025-10-19
* @author     Tran Nam
*             
* @brief      
************************************************************************/


#ifndef HLK_LD2460_H
#define HLK_LD2460_H

#include <stdint.h>
#include <stdbool.h>
#include "common.h"
#ifdef __cplusplus //cplusplus
extern "C" {
#endif

/*       Frame header     */
#define HLK_HDR0         0xF4
#define HLK_HDR1         0xF3   
#define HLK_HDR2         0xF2
#define HLK_HDR3         0xF1

 /*      Frame end         */
#define HLK_TAIL0        0xF8
#define HLK_TAIL1        0xF7
#define HLK_TAIL2        0xF6
#define HLK_TAIL3        0xF5

#define HLK_FUNC_REPORT  0x04 //Functioncode

#ifndef HLK_MAX_TARGETS   // MAX PERSION
#define HLK_MAX_TARGETS 5 // MAX 5 HUMAN
#endif

typedef struct 
{
    float x_m;  // X-axispositionoftarget1(accuracy0.1) 0.1m
    float y_m;  // Y-axispositionoftarget1(accuracy0.1) 0.1m
} HLK_Target;

typedef struct 
{
    uint8_t num_targets;
    HLK_Target t[HLK_MAX_TARGETS];
} HLK_Report;

typedef struct 
{
    uint8_t  buf[256];   
    uint16_t len;        
    uint16_t need;      
    HLK_Report last;     
    bool has_report;
} HLK_CTX;

void HLK_Init(HLK_CTX *ctx);
void HLK_FeedByte(HLK_CTX *ctx, uint8_t byte);
bool HLK_TryGetReport(HLK_CTX *ctx, HLK_Report *out);

#ifdef __cplusplus
}
#endif //cplusplus
#endif  //HLK_LD2460_H
