#include <iostream>
#include <csetjmp>
#include <csignal>
#include <cifuzz/cifuzz.h>

#include "parser.h"

std::jmp_buf my_jump_buffer;

void signalHandler(int signum){
    std::cout << "###### Interrupt signal (" << signum << ") received." << std::endl;
    std::longjmp(my_jump_buffer, 1);
    std::cout << "########### !!!!!! NEVER be printed!!!!!" << std::endl;
    return;
}

FUZZ_TEST_SETUP() {
    signal(SIGABRT, signalHandler);
}

FUZZ_TEST(const uint8_t *data, size_t size)
{

    int val = setjmp(my_jump_buffer);
    if (val == 0){
    //    std::cout << "###### Execute SUT" << std::endl;
        parser(data, size);
    //    std::cout << "###### Execute finished" << std::endl;
    }
    else{
        std::cout << "###### It has been jumped" << std::endl;
    }

}
