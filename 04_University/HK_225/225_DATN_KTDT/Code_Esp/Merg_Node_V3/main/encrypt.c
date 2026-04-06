/**
 * @brief Implementation of the Ascon AEAD Encryption process.
 * @details This function follows the NIST Lightweight Cryptography (LWC) 
 * standard flow for Authenticated Encryption with Associated Data (AEAD).
 * Steps:
 * 1. Validate pointers and input lengths.
 * 2. Calculate the total output length (Plaintext + Authentication Tag).
 * 3. Call the internal core engine to perform initialization, 
 * AD processing, encryption, and tag generation.
 * @param[out] c     Pointer to the ciphertext buffer (must be mlen + CRYPTO_ABYTES).
 * @param[out] clen  Pointer to store the resulting ciphertext length.
 * @param[in]  m     Pointer to the plaintext message buffer.
 * @param[in]  mlen  Length of the plaintext message in bytes.
 * @param[in]  ad    Pointer to the associated data (header/metadata).
 * @param[in]  adlen Length of the associated data.
 * @param[in]  nsec  Secret nonce (not used in Ascon-128).
 * @param[in]  npub  Pointer to the 128-bit public nonce.
 * @param[in]  k     Pointer to the 128-bit secret key.
 * @return int 0 on success, -1 on invalid input parameters.
 */
 
#include "ascon.h"

int crypto_aead_encrypt(unsigned char *c, unsigned long long *clen,
                        const unsigned char *m, unsigned long long mlen,
                        const unsigned char *ad, unsigned long long adlen,
                        const unsigned char *nsec, const unsigned char *npub,
                        const unsigned char *k)
{
    /* 1. Critical Input Validation */
    // Ensure all mandatory buffers and keys are provided
    if ((c == NULL) || (clen == NULL) || (npub == NULL) || (k == NULL))
    {
        return -1;
    }
    /* 2. Consistency Checks */
    // If a length is specified, the corresponding pointer must not be NULL
    if ((m == NULL) && (mlen != 0u))
    {
        return -1;
    }

    if ((ad == NULL) && (adlen != 0u))
    {
        return -1;
    }
    
    /* 3. Parameter Preparation */
    (void)nsec; // Avoid compiler warning for unused parameter
    
    /* Total ciphertext length = message length + size of the authentication tag */
    *clen = mlen + CRYPTO_ABYTES;
    
	 /* 4. Core Engine Execution */
	 /**
	 * Call ascon_core with mode '1' (Encryption mode).
	 * This will perform: Initialization -> AD Absorption -> Encryption -> Finalization
	 */
    return ascon_core(c, m, (unsigned int)mlen, ad, (unsigned int)adlen, npub, k, 1u);
}
