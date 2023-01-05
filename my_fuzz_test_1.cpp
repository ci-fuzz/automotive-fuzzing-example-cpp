#include <iostream>
#include <cassert>

#include <cifuzz/cifuzz.h>

#include "target.h"

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.
}

FUZZ_TEST(const uint8_t *data, size_t size) {

  start_thread0(data, size);
}

