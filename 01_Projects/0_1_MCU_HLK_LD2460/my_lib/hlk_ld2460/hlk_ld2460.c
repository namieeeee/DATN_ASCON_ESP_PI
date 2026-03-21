#include "hlk_ld2460.h"
#include "init.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h> 
static const uint8_t HLK_EN_REPORT[] = {
    0xFD,0xFC,0xFB,0xFA,   // header
    0x0B,                  // length byte
    0x0C,0x00,
    0x01,
    0x04,0x03,0x02,0x01    // tail
};


static inline uint16_t u16_le(const uint8_t *p) {
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static void fr_reset(HLK_CTX *ctx) {
    ctx->len  = 0;
    ctx->need = 0;
}


static bool parse_report(const uint8_t *buf, uint16_t len, HLK_Report *out)
{
    if (!buf || !out) return false;

    /* T?i thi?u 15 byte: F4 F3 F2 F1 04 LL LH ... F8 F7 F6 F5 */
    if (len < 15) return false;

    /* Header */
    if (buf[0] != HLK_HDR0 || buf[1] != HLK_HDR1 ||
        buf[2] != HLK_HDR2 || buf[3] != HLK_HDR3)
        return false;

    /* Function code 0x04 (report) */
    if (buf[4] != HLK_FUNC_REPORT)
        return false;

    /* Ð? dài theo 2 cách:
       - Ki?u A: L = TOTAL (t?ng s? byte c?a c? khung)
       - Ki?u B: L = PAYLOAD (khi dó TOTAL = 7 + L + 4) */
    uint16_t L = u16_le(&buf[5]);
    bool okA = (L == len);
    bool okB = ((uint16_t)(7 + L + 4) == len);

    if (!okA && !okB)
        return false;

    /* Tail */
    if (buf[len-4] != HLK_TAIL0 || buf[len-3] != HLK_TAIL1 ||
        buf[len-2] != HLK_TAIL2 || buf[len-1] != HLK_TAIL3)
        return false;

    /* Payload = N*4 (m?i m?c tiêu: X(2B), Y(2B)) */
    uint16_t payload = okA ? (uint16_t)(L - 11) /* TOTAL - (hdr4 + func1 + len2 + tail4) */
                           : (uint16_t)L;       /* PAYLOAD dã là N*4 */

    if ((payload % 4) != 0)
        return false;

    uint8_t n = (uint8_t)(payload / 4);
    if (n > HLK_MAX_TARGETS) n = HLK_MAX_TARGETS;

    /* Gi?i mã to? d?: don v? 0.1 m -> m */
    out->num_targets = n;
    const uint8_t *p = &buf[7]; /* d? li?u b?t d?u ngay sau len */
    for (uint8_t i = 0; i < n; i++) {
        uint16_t xraw = u16_le(p); p += 2;
        uint16_t yraw = u16_le(p); p += 2;
        out->t[i].x_m = xraw * 0.1f;
        out->t[i].y_m = yraw * 0.1f;
    }
    return true;
}


void HLK_Init(HLK_CTX *ctx)
{
	  HAL_UART_Transmit(&UART1_Handle, (uint8_t*)HLK_EN_REPORT, sizeof(HLK_EN_REPORT), 50);
    if (!ctx) return;
    fr_reset(ctx);
    ctx->has_report = false;
    ctx->last.num_targets = 0;
}


void HLK_FeedByte(HLK_CTX *ctx, uint8_t b)
{
    if (!ctx) return;

    if (ctx->len >= sizeof(ctx->buf)) {
        fr_reset(ctx);
    }

    /* header 4 byte */
    if (ctx->len == 0) { if (b != HLK_HDR0) return; }
    ctx->buf[ctx->len++] = b;

    if (ctx->len == 1 && ctx->buf[0]!=HLK_HDR0) { fr_reset(ctx); return; }
    if (ctx->len == 2 && ctx->buf[1]!=HLK_HDR1) { fr_reset(ctx); return; }
    if (ctx->len == 3 && ctx->buf[2]!=HLK_HDR2) { fr_reset(ctx); return; }
    if (ctx->len == 4 && ctx->buf[3]!=HLK_HDR3) { fr_reset(ctx); return; }


		if (ctx->len == 7)
		{
				if (ctx->buf[4] != HLK_FUNC_REPORT) { fr_reset(ctx); return; }

				uint16_t L = (uint16_t)ctx->buf[5] | ((uint16_t)ctx->buf[6] << 8);


				uint16_t need_A = L;                  
				uint16_t need_B = (uint16_t)(7 + L + 4);

				uint16_t need = 0;
				if (need_A >= 15 && need_A <= sizeof(ctx->buf)) {
						need = need_A;
				} else if (need_B >= 15 && need_B <= sizeof(ctx->buf)) {
						need = need_B;
				} else {
						fr_reset(ctx); return;
				}
				ctx->need = need;
		}


    if (ctx->need && ctx->len == ctx->need) 
		{
			
        HLK_Report rpt;
        if (parse_report(ctx->buf, ctx->len, &rpt)) 
				{
            ctx->last = rpt;
            ctx->has_report = true;
        }
        fr_reset(ctx);
    }
}

bool HLK_TryGetReport(HLK_CTX *ctx, HLK_Report *out)
{
    if (!ctx || !out) return false;
    if (!ctx->has_report) return false;
    *out = ctx->last;
    ctx->has_report = false;
    return true;
}
