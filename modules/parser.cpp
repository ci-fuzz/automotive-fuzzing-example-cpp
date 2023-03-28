#include <csignal>
#include <iostream>

#include "check.h"
#include "parser.h"


#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
    #define NOEXCEPT false
#else
    #define NOEXCEPT true
#endif

uint8_t parser(const uint8_t * const message, size_t len) noexcept(NOEXCEPT){
//    std::cout << "###### parser function" << std::endl;
    
    if (len > 4) {
        check(message);
//        std::cout << "###### will be printed when it meets the verification!" << std::endl;
    }    

    return 0;
}