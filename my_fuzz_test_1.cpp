#include <iostream>
#include <cassert>

#include <cifuzz/cifuzz.h>

#include "target.h"


FUZZ_TEST(const uint8_t *data, size_t size) {

  third_party_library_calc_hmac(data, size);
}
