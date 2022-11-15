#include <string.h>

#include "GPS_module_types.h"
#include "GPS_module_1.h"

#include "crypto_module_types.h"
#include "crypto_module_1.h"

#include "key_management_module_1.h"

namespace GPS {

    position current_destination;

    enum return_status init_crypto_module() {
        crypto::init();
        crypto::key k = {0};
        key_management::create_key(&(k.key[0]), sizeof(k));
        if (crypto::set_key(k) == crypto::valid_key_provided) {
            crypto::nonce n = {0};
            key_management::create_nonce(&(n.nonce[0]), sizeof(n));
            if (crypto::set_nonce(n) == crypto::valid_nonce_provided) {
                return success;
            }
        }
        return failure;
    }

    enum return_status set_destination_position(position pos) {
        current_destination = pos;
        return success;
    }

    position get_destination_position() {
        return current_destination;
    }

    enum return_status get_current_position(position * pos) {
        uint8_t position_as_bytes[12];
        crypto::hmac h = {0};
        if (GPS_driver_obtain_current_position(position_as_bytes, h.hmac) == 0) {
            if (crypto::verify_hmac(position_as_bytes, 16, &h) == crypto::valid_hmac) {
                pos->latitude_degree = position_as_bytes[0] << 1 + position_as_bytes[1];
                pos->latitude_minute = position_as_bytes[2] << 1 + position_as_bytes[3];
                pos->latitude_second = position_as_bytes[4] << 1 + position_as_bytes[5];
                pos->longitude_degree = position_as_bytes[6] << 1 + position_as_bytes[7];
                pos->longitude_minute = position_as_bytes[8] << 1 + position_as_bytes[9];
                pos->longitude_second = position_as_bytes[10] << 1 + position_as_bytes[11];
                return success;
            }
        }
        return failure;
    }

}

uint8_t GPS_driver_obtain_current_position(uint8_t * position_as_bytes, uint8_t * hmac_as_bytes) {
    return 0;
}