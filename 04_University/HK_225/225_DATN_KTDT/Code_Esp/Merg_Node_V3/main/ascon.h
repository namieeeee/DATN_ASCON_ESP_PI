/******************************************************************************
 * @file    ascon.h
 * @brief   Core functions for Ascon Authenticated Encryption (AEAD).
 *
 * @details This file provides the API for encrypting and decrypting data 
 * using the Ascon-128 algorithm. It supports Authenticated Encryption 
 * with Associated Data (AEAD) to ensure both confidentiality and integrity.
 *
 * @author  Tran Nam
 * @date    2026-03-28
 * @version 1.0
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/
#ifndef ASCON_H
#define ASCON_H

#include "api.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Encrypts a message using Ascon AEAD.
 * * @param[out] c     Pointer to the ciphertext output buffer.
 * @param[out] clen  Pointer to the length of the ciphertext produced.
 * @param[in]  m     Pointer to the plaintext message buffer.
 * @param[in]  mlen  Length of the plaintext message in bytes.
 * @param[in]  ad    Pointer to the associated data (header/metadata).
 * @param[in]  adlen Length of the associated data.
 * @param[in]  nsec  Secret nonce (typically not used, set to NULL).
 * @param[in]  npub  Pointer to the public nonce (CRYPTO_NPUBBYTES).
 * @param[in]  k     Pointer to the secret key (CRYPTO_KEYBYTES).
 * * @return int 0 on success, non-zero otherwise.
 **/
 
int crypto_aead_encrypt(unsigned char *c, unsigned long long *clen,
                        const unsigned char *m, unsigned long long mlen,
                        const unsigned char *ad, unsigned long long adlen,
                        const unsigned char *nsec, const unsigned char *npub,
                        const unsigned char *k);

/**
 * @brief Decrypts and verifies a ciphertext using Ascon AEAD.
 * @param[out] m     Pointer to the recovered plaintext buffer.
 * @param[out] mlen  Pointer to the length of the recovered plaintext.
 * @param[out] nsec  Secret nonce (typically not used, set to NULL).
 * @param[in]  c     Pointer to the ciphertext input buffer.
 * @param[in]  clen  Length of the ciphertext in bytes.
 * @param[in]  ad    Pointer to the associated data.
 * @param[in]  adlen Length of the associated data.
 * @param[in]  npub  Pointer to the public nonce.
 * @param[in]  k     Pointer to the secret key.
 * * @return int 0 if authentication and decryption succeed, -1 if verification fails.
 */
 
int crypto_aead_decrypt(unsigned char *m         , unsigned long long *mlen,
                        unsigned char *nsec      , const unsigned char *c,
                        unsigned long long clen  , const unsigned char *ad,
                        unsigned long long adlen , const unsigned char *npub,
                        const unsigned char *k);
                        
/**
 * @brief Internal core function for Ascon permutation and logic.
 * * @details This function handles the low-level state transitions of the Ascon cipher.
 * @return int 0 on success.
 */
 
int ascon_core(unsigned char *outptr    , const unsigned char *inptr,
               unsigned int inlen       , const unsigned char *adptr,
               unsigned int adlen       , const unsigned char *nptr,
               const unsigned char *kptr, unsigned char mode);

#ifdef __cplusplus
}
#endif

#endif /* ASCON_H */
