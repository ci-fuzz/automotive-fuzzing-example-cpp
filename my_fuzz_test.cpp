#include <cifuzz/cifuzz.h>
#include <iostream>

#include "parser.h"

FUZZ_TEST(const uint8_t *data, size_t size)
{
    parser(data, size);
}
