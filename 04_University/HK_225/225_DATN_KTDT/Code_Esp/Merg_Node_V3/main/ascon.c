/******************************************************************************
 * @file    ascon.c
 * @brief   Implementation of Ascon-128 Authenticated Encryption (AEAD).
 *
 * @details This file contains the core logic for the Ascon permutation and 
 * provides the high-level API for encryption and decryption. The implementation 
 * is optimized for 8-bit/32-bit microcontrollers like ESP32.
 *
 * @author  Tran Nam
 * @date    2026-03-28
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/

#include "ascon.h"

#include <stdint.h>
#include <string.h>

typedef struct
{
    uint64_t x0;
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
} ascon_state_t;

#define ASCON_AEAD128_RATE_BYTES 16u
#define ASCON_PA_ROUNDS          12u
#define ASCON_PB_ROUNDS          8u
#define ASCON_AEAD128_IV         UINT64_C(0x00001000808c0001)

static const uint8_t k_round_constants[16] = {
    0x3c  , 0x2d  , 0x1e  , 0x0f,
    0xf0  , 0xe1  , 0xd2  , 0xc3,
    0xb4  , 0xa5  , 0x96 , 0x87,
    0x78 , 0x69 , 0x5a , 0x4b
};

static void ascon_secure_zero(void *buffer, size_t size)
{
    volatile uint8_t *p = (volatile uint8_t *)buffer;

    while (size-- > 0u)
    {
        *p++ = 0u;
    }
}

static inline uint64_t
ascon_rotr64(uint64_t x, unsigned int n)
{
    return (x >> n) | (x << (64u - n));
}

static uint64_t
ascon_load64_le(const unsigned char *src)
{
    return ((uint64_t)src[0]) |
           ((uint64_t)src[1] << 8) |
           ((uint64_t)src[2] << 16) |
           ((uint64_t)src[3] << 24) |
           ((uint64_t)src[4] << 32) |
           ((uint64_t)src[5] << 40) |
           ((uint64_t)src[6] << 48) |
           ((uint64_t)src[7] << 56);
}

static void
ascon_store64_le(unsigned char *dst, uint64_t x)
{
    dst[0] = (unsigned char)(x);
    dst[1] = (unsigned char)(x >> 8);
    dst[2] = (unsigned char)(x >> 16);
    dst[3] = (unsigned char)(x >> 24);
    dst[4] = (unsigned char)(x >> 32);
    dst[5] = (unsigned char)(x >> 40);
    dst[6] = (unsigned char)(x >> 48);
    dst[7] = (unsigned char)(x >> 56);
}

static void
ascon_round(ascon_state_t *state, uint8_t rc)
{
    uint64_t t0;
    uint64_t t1;
    uint64_t t2;
    uint64_t t3;
    uint64_t t4;

    state->x2 ^= (uint64_t)rc;

    state->x0 ^= state->x4;
    state->x4 ^= state->x3;
    state->x2 ^= state->x1;

    t0 = (~state->x0) & state->x1;
    t1 = (~state->x1) & state->x2;
    t2 = (~state->x2) & state->x3;
    t3 = (~state->x3) & state->x4;
    t4 = (~state->x4) & state->x0;

    state->x0 ^= t1;
    state->x1 ^= t2;
    state->x2 ^= t3;
    state->x3 ^= t4;
    state->x4 ^= t0;

    state->x1 ^= state->x0;
    state->x0 ^= state->x4;
    state->x3 ^= state->x2;
    state->x2 = ~state->x2;

    state->x0 ^= ascon_rotr64(state->x0, 19u) ^ ascon_rotr64(state->x0, 28u);
    state->x1 ^= ascon_rotr64(state->x1, 61u) ^ ascon_rotr64(state->x1, 39u);
    state->x2 ^= ascon_rotr64(state->x2, 1u) ^ ascon_rotr64(state->x2, 6u);
    state->x3 ^= ascon_rotr64(state->x3, 10u) ^ ascon_rotr64(state->x3, 17u);
    state->x4 ^= ascon_rotr64(state->x4, 7u) ^ ascon_rotr64(state->x4, 41u);
}

static void
ascon_permute(ascon_state_t *state, unsigned int rounds)
{
    unsigned int i;
    const unsigned int start = 16u - rounds;

    for (i = start; i < 16u; ++i)
    {
        ascon_round(state, k_round_constants[i]);
    }
}

static void
ascon_init(ascon_state_t *state, const unsigned char *nonce,
           const unsigned char *key)
{
    const uint64_t k0 = ascon_load64_le(&key[0]);
    const uint64_t k1 = ascon_load64_le(&key[8]);

    state->x0 = ASCON_AEAD128_IV;
    state->x1 = k0;
    state->x2 = k1;
    state->x3 = ascon_load64_le(&nonce[0]);
    state->x4 = ascon_load64_le(&nonce[8]);

    ascon_permute(state, ASCON_PA_ROUNDS);

    state->x3 ^= k0;
    state->x4 ^= k1;
}

static void ascon_absorb_ad(ascon_state_t *state, const unsigned char *ad,
                unsigned int adlen)
{
    unsigned char last_block[ASCON_AEAD128_RATE_BYTES];
    unsigned int full_blocks;
    unsigned int remainder;
    unsigned int i;

    if ((ad == NULL) || (adlen == 0u))
    {
        state->x4 ^= UINT64_C(1);
        return;
    }

    full_blocks = adlen / ASCON_AEAD128_RATE_BYTES;
    remainder = adlen % ASCON_AEAD128_RATE_BYTES;

    for (i = 0u; i < full_blocks; ++i)
    {
        const unsigned char *block = &ad[i * ASCON_AEAD128_RATE_BYTES];

        state->x0 ^= ascon_load64_le(&block[0]);
        state->x1 ^= ascon_load64_le(&block[8]);
        ascon_permute(state, ASCON_PB_ROUNDS);
    }

    (void)memset(last_block, 0, sizeof(last_block));
    if (remainder > 0u)
    {
        (void)memcpy(last_block, &ad[full_blocks * ASCON_AEAD128_RATE_BYTES], remainder);
    }
    last_block[remainder] = 0x01u;

    state->x0 ^= ascon_load64_le(&last_block[0]);
    state->x1 ^= ascon_load64_le(&last_block[8]);
    ascon_permute(state, ASCON_PB_ROUNDS);

    state->x4 ^= UINT64_C(1);
    ascon_secure_zero(last_block, sizeof(last_block));
}

static void ascon_encrypt_msg(ascon_state_t *state, unsigned char *ciphertext,
                  const unsigned char *plaintext, unsigned int plaintext_len)
{
    unsigned char rate_bytes[ASCON_AEAD128_RATE_BYTES];
    unsigned int full_blocks = plaintext_len / ASCON_AEAD128_RATE_BYTES;
    unsigned int remainder = plaintext_len % ASCON_AEAD128_RATE_BYTES;
    unsigned int offset = 0u;
    unsigned int i;

    for (i = 0u; i < full_blocks; ++i)
    {
        const unsigned char *block = &plaintext[offset];

        state->x0 ^= ascon_load64_le(&block[0]);
        state->x1 ^= ascon_load64_le(&block[8]);
        ascon_store64_le(&ciphertext[offset], state->x0);
        ascon_store64_le(&ciphertext[offset + 8u], state->x1);

        offset += ASCON_AEAD128_RATE_BYTES;
        ascon_permute(state, ASCON_PB_ROUNDS);
    }

    ascon_store64_le(&rate_bytes[0], state->x0);
    ascon_store64_le(&rate_bytes[8], state->x1);

    for (i = 0u; i < remainder; ++i)
    {
        rate_bytes[i] ^= plaintext[offset + i];
        ciphertext[offset + i] = rate_bytes[i];
    }
    rate_bytes[remainder] ^= 0x01u;

    state->x0 = ascon_load64_le(&rate_bytes[0]);
    state->x1 = ascon_load64_le(&rate_bytes[8]);

    ascon_secure_zero(rate_bytes, sizeof(rate_bytes));
}

static void ascon_decrypt_msg(ascon_state_t *state, unsigned char *plaintext,
                  const unsigned char *ciphertext, unsigned int ciphertext_len)
{
    unsigned char rate_bytes[ASCON_AEAD128_RATE_BYTES];
    unsigned int full_blocks = ciphertext_len / ASCON_AEAD128_RATE_BYTES;
    unsigned int remainder = ciphertext_len % ASCON_AEAD128_RATE_BYTES;
    unsigned int offset = 0u;
    unsigned int i;

    for (i = 0u; i < full_blocks; ++i)
    {
        const unsigned char *block = &ciphertext[offset];
        const uint64_t c0 = ascon_load64_le(&block[0]);
        const uint64_t c1 = ascon_load64_le(&block[8]);

        ascon_store64_le(&plaintext[offset], state->x0 ^ c0);
        ascon_store64_le(&plaintext[offset + 8u], state->x1 ^ c1);

        state->x0 = c0;
        state->x1 = c1;

        offset += ASCON_AEAD128_RATE_BYTES;
        ascon_permute(state, ASCON_PB_ROUNDS);
    }

    ascon_store64_le(&rate_bytes[0], state->x0);
    ascon_store64_le(&rate_bytes[8], state->x1);

    for (i = 0u; i < remainder; ++i)
    {
        plaintext[offset + i] = (unsigned char)(rate_bytes[i] ^ ciphertext[offset + i]);
        rate_bytes[i] = ciphertext[offset + i];
    }
    rate_bytes[remainder] ^= 0x01u;

    state->x0 = ascon_load64_le(&rate_bytes[0]);
    state->x1 = ascon_load64_le(&rate_bytes[8]);

    ascon_secure_zero(rate_bytes, sizeof(rate_bytes));
}

static void ascon_finalize(ascon_state_t *state, const unsigned char *key,
               unsigned char *tag)
{
    const uint64_t k0 = ascon_load64_le(&key[0]);
    const uint64_t k1 = ascon_load64_le(&key[8]);

    state->x2 ^= k0;
    state->x3 ^= k1;
    ascon_permute(state, ASCON_PA_ROUNDS);
    state->x3 ^= k0;
    state->x4 ^= k1;

    ascon_store64_le(&tag[0], state->x3);
    ascon_store64_le(&tag[8], state->x4);
}

static unsigned char ascon_ct_diff(const unsigned char *a, const unsigned char *b, unsigned int len)
{
    unsigned int i;
    unsigned char diff = 0u;

    for (i = 0u; i < len; ++i)
    {
        diff |= (unsigned char)(a[i] ^ b[i]);
    }

    return diff;
}

int ascon_core(unsigned char *outptr, const unsigned char *inptr,
               unsigned int inlen, const unsigned char *adptr,
               unsigned int adlen, const unsigned char *nptr,
               const unsigned char *kptr, unsigned char mode)
{
    ascon_state_t state;
    unsigned char computed_tag[CRYPTO_ABYTES];
    int result = -1;

    if ((outptr == NULL) || (nptr == NULL) || (kptr == NULL))
    {
        return -1;
    }

    if ((inptr == NULL) && (inlen != 0u))
    {
        return -1;
    }

    if ((adptr == NULL) && (adlen != 0u))
    {
        return -1;
    }

    ascon_init(&state, nptr, kptr);
    ascon_absorb_ad(&state, adptr, adlen);

    if ((int8_t)mode > 0)
    {
        ascon_encrypt_msg(&state, outptr, inptr, inlen);
        ascon_finalize(&state, kptr, &outptr[inlen]);
        result = 0;
        goto exit;
    }

    if ((int8_t)mode < 0)
    {
        const unsigned char *tagptr = &inptr[inlen];

        ascon_decrypt_msg(&state, outptr, inptr, inlen);
        ascon_finalize(&state, kptr, computed_tag);

        if (ascon_ct_diff(computed_tag, tagptr, CRYPTO_ABYTES) != 0u)
        {
            ascon_secure_zero(outptr, inlen);
            result = -1;
            goto exit;
        }

        result = 0;
        goto exit;
    }

exit:
    ascon_secure_zero(computed_tag, sizeof(computed_tag));
    ascon_secure_zero(&state, sizeof(state));
    return result;
}
