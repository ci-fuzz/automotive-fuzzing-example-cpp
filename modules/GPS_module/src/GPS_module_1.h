#ifndef GPS_MODULE_1_H
#define GPS_MODULE_1_H

#include "GPS_module_types.h"

uint8_t GPS_driver_obtain_current_position(uint8_t * position_as_bytes, uint8_t * hmac_as_bytes);

namespace GPS {

enum return_status init_crypto_module();

enum return_status set_destination_position(position pos);

position get_destination_position();

enum return_status get_current_position(position * pos);

}

#endif