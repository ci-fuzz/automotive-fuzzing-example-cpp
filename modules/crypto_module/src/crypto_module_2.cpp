#include "crypto_module_types.h"
#include "crypto_module_2.h"

#include "time_module_1.h"

namespace crypto {

    enum return_status verify_nonce(nonce * n) {
        for (int i = 0; i < NONCE_LENGTH; i++ ) {
            if (n->nonce[i] != 0) {
                if (n->time_of_creation > time_management::current_time() - 300) {
                    return valid_nonce_provided;
                }
            }
        }
        //Nonce is only zero
        return invalid_nonce_provided;
    }


    enum return_status verify_key(key k) {
        for (int i = 0; i < KEY_LENGTH; i++ ) {
            if (k.key[i] != 0) {
                return valid_key_provided;
            }
        }
        //Key is only zero
        return invalid_key_provided;
    }

}