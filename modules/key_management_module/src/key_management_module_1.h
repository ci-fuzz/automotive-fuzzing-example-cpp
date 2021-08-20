#ifndef KEY_MANAGEMENT_MODULE_1_H
#define KEY_MANAGEMENT_MODULE_1_H

#include <stdint.h>

#include "key_management_module_types.h"

uint8_t HSM_get_random_byte();

namespace key_management {

    void create_key(uint8_t * key, uint8_t length);
    void create_nonce(uint8_t * nonce, uint8_t length);
    uint8_t * generate_random_bytes(uint8_t * buffer, uint8_t length);

}
#endif