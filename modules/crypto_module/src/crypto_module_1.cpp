#include <string.h>
#include <iostream>
#include "crypto_module_1.h"
#include "crypto_module_2.h"

namespace crypto {

    static enum state current_state = uninitialized;
    static key current_key = {0};
    static nonce * current_nonce = (nonce*)calloc(1, sizeof(nonce));

    void init() {
        memset(&current_key, 0 , sizeof(current_key));
        memset(current_nonce, 0 , sizeof(nonce));
        current_state = initialized;
    }

    state get_state() {
        return current_state;
    }

    return_status set_key(key k) {
        if (verify_key(k) == valid_key_provided) {
            current_key = k;
            if (current_state == nonce_set) {
                current_state = nonce_and_key_set;
            }
            else {
                current_state = key_set;
            }
            return valid_key_provided;
        }
        return invalid_key_provided;
    }

    return_status set_nonce(nonce n) {
        if(verify_nonce(&n) == valid_nonce_provided) {
            for (int i = 0; i < NONCE_LENGTH; i++) {
                current_nonce->nonce[i] = n.nonce[i];
            }
            current_nonce->time_of_creation = n.time_of_creation;
            if (current_state == key_set) {
                current_state = nonce_and_key_set;
            }
            else {
                current_state = nonce_set;
            }
            return valid_nonce_provided;
        }
        return invalid_nonce_provided;
    }

    return_status calculate_hmac(const uint8_t * const message, size_t len, hmac * h) {
        if (current_state == nonce_and_key_set) {
            if (current_nonce != 0) {
                if (third_party_library_calc_hmac(message, len, (char*) &(current_key.key[0]), (char*)current_nonce, h->hmac) == 0) {
                    //Delete nonce to make sure it is only used once
                    //free(current_nonce);
                    //current_nonce = 0;
                    return hmac_successfully_calculated;
                }
            }
            current_state = initialized;
            std::cout << "[ERROR] Error during hmac calculation!";
            return error_during_hmac_calculation;
        }
        return wrong_state;
    }

    return_status verify_hmac(const uint8_t * const message, size_t len, hmac * h) {
        hmac own_hmac;
        return_status hmac_calc_status = calculate_hmac(message, len, &own_hmac);
        if (hmac_calc_status != hmac_successfully_calculated) {
            return hmac_calc_status;
        }
        for (int i = 0; i < HMAC_LENGTH; i++) {
            if (own_hmac.hmac[i] != h->hmac[i]) {
                return invalid_hmac;
            } 
        }
        return valid_hmac;
    }

}

uint8_t third_party_library_calc_hmac(const uint8_t * const message, size_t len, char * const key, char * const nonce, uint8_t * hmac) {
    if (len > 4) {
        if (message[0] == 1) {
            if (message[1] == 2) {            
                if (message[2] == 3) {               
                    if (message[3] == 4) {
                        int x[3];
                        int y = 4;
                        int z = x[y];
                    }   
                }   
            }   
        }
    }
    return 0;
}