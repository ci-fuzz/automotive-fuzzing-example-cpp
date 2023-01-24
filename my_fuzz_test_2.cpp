#include <iostream>
#include <cifuzz/cifuzz.h>

#include "target.h"

// Mocked function
extern "C" uint8_t __wrap__Z6parserh(){
    std::cout << "###### wrapped parser function" << std::endl;
    return 0;
}

FUZZ_TEST(const uint8_t *data, size_t size) {
    UBSanFinding(data, size);
}
