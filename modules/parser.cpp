#include <csignal>
#include <iostream>

#include "parser.h"

uint8_t parser(uint8_t sigCase){
    std::cout << "###### parser function" << std::endl;
    switch (sigCase%6)
    {
    case 0:
        std::raise(SIGABRT);
        break;
    case 1:
        std::raise(SIGFPE);
        break;
    case 2:
        std::raise(SIGILL);
        break;
    case 3:
        std::raise(SIGINT);
        break;
    case 4:
        std::raise(SIGSEGV);
        break;
    case 5:
        std::raise(SIGTERM);
        break;
    default:
        break;
    }
    

    return 0;
}