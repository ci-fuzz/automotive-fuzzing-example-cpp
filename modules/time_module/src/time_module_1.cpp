#include "time_module_1.h"

namespace time_management {

    int current_time() {
        return driver_get_current_time();
    }

}

int driver_get_current_time() {
    return 0;
}