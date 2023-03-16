#include <stddef.h>

#include "target.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    UBSanFinding(data, size);
    return 0;
}

