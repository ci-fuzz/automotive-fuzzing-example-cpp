#ifndef CRYPTO_MODULE_1_H
#define CRYPTO_MODULE_1_H

#include <stdint.h>

#include "crypto_module_types.h"

extern int third_party_library_calc_hmac(const uint8_t * const message, int len, char * const key, char * const nonce, uint8_t * hmac);

namespace crypto
{
    void init();

    state get_state();

    return_status set_key(key k);

    return_status set_nonce(nonce n);

    return_status calculate_hmac(const uint8_t * const message, int len, hmac * h);

    return_status verify_hmac(const uint8_t * const message, int len, hmac * h);

} // namespace crypto

#endif