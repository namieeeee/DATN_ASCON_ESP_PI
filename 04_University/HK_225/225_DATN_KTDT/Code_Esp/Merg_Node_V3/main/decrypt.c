/******************************************************************************
 * @file    ascon.c
 * @brief   Implementation of Ascon-128 Authenticated Encryption (AEAD).
 *
 * @details This file contains the implementation of the Ascon-128 encryption 
 * and decryption algorithms. It manages the 320-bit internal state 
 * permutations and provides the high-level API for secure data 
 * transmission between ESP32 and other peripherals.
 *
 * @author  Tran Nam
 * @date    2026-03-28
 * @version 1.0
 *
 * @note    - Optimized for 32-bit architecture (ESP32).
 * - Compliant with NIST Lightweight Cryptography (LWC) standards.
 * - Requires api.h for hardware-specific constants.
 *
 * @warning Ensure that the nonce (npub) is never reused for the same key 
 * to maintain the security properties of the AEAD scheme.
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/


#include "ascon.h"
#include <string.h>

/**
 * @brief Implementation of the Ascon AEAD Decryption and Verification.
 * * @param[out] m     Pointer to the recovered plaintext buffer.
 * @param[out] mlen  Pointer to the length of the recovered plaintext.
 * @param[out] nsec  Secret nonce (not used, kept for API compatibility).
 * @param[in]  c     Pointer to the ciphertext input buffer.
 * @param[in]  clen  Length of the ciphertext (including the tag).
 * @param[in]  ad    Pointer to the associated data.
 * @param[in]  adlen Length of the associated data.
 * @param[in]  npub  Pointer to the public nonce.
 * @param[in]  k     Pointer to the secret key.
 * * @return int 0 if authentication succeeds; -1 if verification fails or inputs are invalid.
 */
 
int crypto_aead_decrypt(unsigned char *m, unsigned long long *mlen,
                        unsigned char *nsec, const unsigned char *c,
                        unsigned long long clen, const unsigned char *ad,
                        unsigned long long adlen, const unsigned char *npub,
                        const unsigned char *k)
{   /* 1. Pre-condition Validation */
    if ((m == NULL) || (mlen == NULL) || (c == NULL) || (npub == NULL) || (k == NULL))
    {
        return -1;
    }
    /* 2. Associated Data Consistency Check */
    if ((ad == NULL) && (adlen != 0u))
    {
        return -1;
    }
    /* 3. Integrity Check: Ciphertext must be at least as long as the Tag */
    if (clen < CRYPTO_ABYTES)
    {
        *mlen = 0u;
        return -1;
    }
    /* 4. Prepare for Decryption Core */
    (void)nsec; // Avoid compiler warning for unused parameter
    
    /* Calculate actual message length (excluding the authentication tag) */
    *mlen = clen - CRYPTO_ABYTES;
    
    /* 5. Execute Ascon Core Engine in Decryption Mode (-1) */
    return ascon_core(m, c, (unsigned int)(clen - CRYPTO_ABYTES), ad, (unsigned int)adlen,
                      npub, k, (unsigned char)-1);
}
