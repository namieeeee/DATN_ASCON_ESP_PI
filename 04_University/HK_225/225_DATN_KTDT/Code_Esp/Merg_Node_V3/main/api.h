/******************************************************************************
 * @file    api.h
 * @brief   Configuration parameters for the Ascon lightweight cryptography.
 *
 * @details This header defines the specific constants for the Ascon-128 
 * Authenticated Encryption with Associated Data (AEAD) implementation,
 * ensuring compliance with NIST lightweight cryptography standards.
 *
 * @author  Tran Nam
 * @date    2026-03-28
 * @version 1.0
 *
 * @note    These parameters are optimized for the ESP32 platform using 
 * fixed-length keys and nonces.
 *
 * @warning Any modification to CRYPTO_KEYBYTES or CRYPTO_NPUBBYTES will 
 * break compatibility with standard Ascon implementations.
 *
 * @copyright (c) 2026 Tran Nam. All rights reserved.
 ******************************************************************************/

#ifndef API_H
#define API_H

/** * @name Ascon-128 AEAD Parameters
 * @{ 
 */
 
/* Implementation version string */
#define CRYPTO_VERSION "sp800-232-secure"

/* Size of the secret key in bytes (128-bit) */
#define CRYPTO_KEYBYTES 16

/* Size of the secret message number (not used) */
#define CRYPTO_NSECBYTES 0

/* Size of the public message number (Nonce) in bytes (128-bit) */
#define CRYPTO_NPUBBYTES 16

/* Size of the authentication tag (MAC) in bytes */
#define CRYPTO_ABYTES 16

/* Buffer overlap restriction (1: No overlap allowed) */
#define CRYPTO_NOOVERLAP 1

/* Data block processing rate (16 bytes for Ascon-128) */
#define ASCON_AEAD_RATE 16

/* Ascon variant: 1 for Ascon-128, 2 for Ascon-128a */
#define ASCON_VARIANT 1
/** @} */
#endif /* API_H */
