#ifndef CRYPTO_MODULE_TYPES_H
#define CRYPTO_MODULE_TYPES_H

#include <stdint.h>

namespace crypto {

    #define NONCE_LENGTH 64
    #define KEY_LENGTH 64
    #define HMAC_LENGTH 64

    enum state{
        uninitialized,
        initialized,
        key_set,
        nonce_set,
        nonce_and_key_set
    };

    typedef struct nonce {
        uint8_t nonce[NONCE_LENGTH];
        int time_of_creation;
    } nonce;

    typedef struct key {
        uint8_t key[KEY_LENGTH];
    } key;

    typedef struct hmac {
        uint8_t hmac[HMAC_LENGTH];
    } hmac;

    typedef struct message {
        uint8_t key[HMAC_LENGTH];
    } message;

    enum return_status {
        valid_key_provided,
        invalid_key_provided,
        valid_nonce_provided,
        invalid_nonce_provided,
        wrong_state,
        hmac_successfully_calculated,
        error_during_hmac_calculation,
        invalid_hmac,
        valid_hmac
    };
}

#endif