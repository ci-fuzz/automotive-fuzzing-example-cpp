#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

#include <cifuzz/cifuzz.h>

#include "target.h"

#define FUZZ

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.
}

FUZZ_TEST(const uint8_t *data, size_t size) {

  UBSanFinding(data, size);

}

