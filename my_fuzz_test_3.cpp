#include <iostream>
#include <csignal>

#include <cifuzz/cifuzz.h>

#include "target.h"

void signalHandler(int signum){
    std::cout << "###### Interrupt signal (" << signum << ") received." << std::endl;

   // cleanup and close up stuff here  
   // terminate program  

    return;
}

FUZZ_TEST_SETUP() {
    signal(SIGABRT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGTERM, signalHandler);
}

FUZZ_TEST(const uint8_t *data, size_t size) {
    UBSanFinding(data, size);
}
