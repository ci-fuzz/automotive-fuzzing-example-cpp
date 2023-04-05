#include <cifuzz/cifuzz.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"

int run;

void signalHandler(int signum){
    std::cout << "###### Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

FUZZ_TEST_SETUP() {
    signal(SIGABRT, signalHandler);
    run = 0;
}


FUZZ_TEST(const uint8_t *data, size_t size)
{
    run++;
//    std::cout << "######## Run: " << run << std::endl;
    pid_t c_pid = fork();
    pid_t w;
    int wstatus;

    if (c_pid == 0)
    {
//        std::cout << "###### Child :" << c_pid << " - " << getpid() << std::endl;
        parser(data, size);
//        std::cout << "###### Child finished:" << std::endl;

    }
    else if (c_pid > 0)
    {
//        std::cout << "###### Parent, wait for child" << std::endl;
        while (waitpid(c_pid, NULL, 0) > 0);
//        std::cout << "###### Parent, child terminated : " << getpid() << std::endl;
    }

//    std::cout << "####### Run finished: " << run << std::endl;
}
