#include <iostream>
#include <csignal>
#include <cassert>

#include <cifuzz/cifuzz.h>
#include <stdexcept>

#include "parser.h"

extern "C" int __wrap_raise(int __sig)
{
    switch (__sig)
    {
    case SIGABRT:
        std::cout << "######## wrapped raise function" << std::endl;
        throw std::runtime_error("oops");
        std::cout << "########### !!!!!! NEVER be printed!!!!!" << std::endl;
        break;
    default:
        std::raise(__sig);
    }
    return 0;
}

FUZZ_TEST(const uint8_t *data, size_t size)
{
    try
    {
        parser(data, size);
    }
    catch (...)
    {
        std::cout << "######### catch exception" << std::endl;
    }
}
