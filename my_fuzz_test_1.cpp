#include <iostream>
#include <cassert>

#include <cifuzz/cifuzz.h>
#include <gtest/gtest.h>

#include "GPS_module_1.h"
#include "crypto_module_1.h"
#include "crypto_module_2.h"
#include "key_management_module_1.h"
#include "time_module_1.h"


FUZZ_TEST(const uint8_t *data, size_t size) {
  crypto::init();

  char * key = NULL;
  char * nonce = NULL;
  uint8_t * hmac = NULL;

  EXPECT_NE(third_party_library_calc_hmac(data, size, key, nonce, hmac),0xFF);
}
