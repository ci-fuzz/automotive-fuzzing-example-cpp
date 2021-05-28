#ifndef GPS_MODULE_TYPES_H
#define GPS_MODULE_TYPES_H

#include <stdint.h>

namespace GPS {

typedef struct position {
    uint8_t longitude_degree;
    uint8_t longitude_minute;
    uint8_t longitude_second;
    uint8_t latitude_degree;
    uint8_t latitude_minute;
    uint8_t latitude_second;
} position;

enum return_status {
    success,
    failure,
};

}

#endif