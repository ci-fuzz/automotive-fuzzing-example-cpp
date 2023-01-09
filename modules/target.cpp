#include <iostream>

#include "target.h"

int activate = 0;


int main(int argc, char *argv[]){

    activate = 1;
    std::cout << "############ Hello From Origin Main! ##############" << std::endl;
    return 0;
}

uint8_t hmac(const uint8_t * const message, size_t len) {
    if (activate){
        if (len > 4) {
            if (message[0] == 'F') {
                if (message[1] == 'U') {            
                    if (message[2] == 'Z') {               
                        if (message[3] == 'Z') {
                            int x[3];
                            int y = 4;
                            int z = x[y];
                        }   
                    }   
                }   
            }
        }
    }
    return 0;
}
