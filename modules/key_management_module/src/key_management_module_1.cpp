#include "key_management_module_1.h"

namespace key_management {

    uint8_t * generate_random_bytes(uint8_t * buffer, uint8_t length) {
        for (int i = 0; i < length; i++) {
            buffer[i] = HSM_get_random_byte();
        }
        return buffer;
    }

    void create_key(uint8_t * key, uint8_t length) {
        generate_random_bytes(key, length);
    }

    void create_nonce(uint8_t * nonce, uint8_t length) {
        generate_random_bytes(nonce, length);
    }

}

uint8_t HSM_get_random_byte() {
    return 0;
}
