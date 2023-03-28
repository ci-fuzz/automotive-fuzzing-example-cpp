#include <iostream>
#include <csignal>
#include "check.h"
#include <stdexcept>

uint8_t check(const uint8_t *const message)
{
//    std::cout << "########### check : " << message[0] << message[1] << message[2] << message[3] << std::endl;
    if (message[0] == 'F')
    {
        if (message[1] == 'U')
        {
            if (message[2] == 'Z')
            {
                if (message[3] == 'Z')
                {
                    std::cout << "####### trigger abort signal " << std::endl;
                    std::raise(SIGABRT);
                    std::cout << "########### !!!!!! this should be never be printed!!!!!" << std::endl;
                }
            }
        }
    }
    return 0;
}
