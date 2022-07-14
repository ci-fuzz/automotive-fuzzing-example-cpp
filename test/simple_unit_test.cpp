#include <iostream>
#include <cassert>

#include "GPS_module_1.h"
#include "crypto_module_1.h"
#include "crypto_module_2.h"
#include "key_management_module_1.h"
#include "time_module_1.h"

#include <gtest/gtest.h>

void test1() {
    crypto::init();
    assert(crypto::get_state() == crypto::initialized);
}



TEST(Test1, Init_Crypto) {
    crypto::init();
    EXPECT_EQ(crypto::get_state(), crypto::initialized);
}

TEST(Test1, Calculate_HMAC) {
    const size_t len = 5;
    const uint8_t message [len] = { 'F', 'U', 'Z', 'Z', '1'};
    char * key = NULL;
    char * nonce = NULL;
    uint8_t * hmac = NULL;

    EXPECT_EQ(third_party_library_calc_hmac((uint8_t*)&message, len, key, nonce, hmac),0);
}
