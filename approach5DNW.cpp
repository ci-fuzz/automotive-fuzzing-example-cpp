#include <iostream>
#include <csetjmp>
#include <csignal>
#include <cifuzz/cifuzz.h>

#include "parser.h"

std::jmp_buf my_jump_buffer;

void signalHandler(int signum){
    std::cout << "###### Interrupt signal (" << signum << ") received." << std::endl;
    throw std::runtime_error("oops");
    std::cout << "########### !!!!!! NEVER be printed!!!!!" << std::endl;
    return;
}

FUZZ_TEST_SETUP() {
    signal(SIGABRT, signalHandler);
}

FUZZ_TEST(const uint8_t *data, size_t size)
{
    try{
        parser(data, size);
    }
    catch(...){
        std::cout << "###### catch exception" << std::endl;
    }
}
