#include <iostream>
#include <cassert>

#include "GPS_module_1.h"
#include "crypto_module_1.h"
#include "crypto_module_2.h"
#include "key_management_module_1.h"
#include "time_module_1.h"

void test1() {
    crypto::init();
    assert(crypto::get_state() == crypto::initialized);
}

void test2() {
    const size_t len = 5;
    const uint8_t message [len] = { 'F', 'U', 'Z', 'Z', '1'};
    char * key = NULL;
    char * nonce = NULL;
    uint8_t * hmac = NULL;

    assert(third_party_library_calc_hmac((uint8_t*)&message, len, key, nonce, hmac) == 0);
}


int main(void) {
    // Call all tests. Using a test framework would simplify this.
    test1();
    test2();
    std::cout << "Test run completed!\n";
}