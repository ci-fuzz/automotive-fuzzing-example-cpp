#include <cifuzz/cifuzz.h>

#include "target.h"

FUZZ_TEST(const uint8_t *data, size_t size) {
    UBSanFinding(data, size);
}

