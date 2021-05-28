#ifndef CRYPTO_MODULE_2_H
#define CRYPTO MODULE_2_H

#include "crypto_module_types.h"
#include "crypto_module_1.h"

namespace crypto
{    
    enum return_status verify_nonce(nonce * n);
    enum return_status verify_key(key k);
} // namespace crypto

#endif