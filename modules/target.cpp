#include <iostream>
#include <thread>
#include <iostream>

#include "target.h"
#include "my_fuzz_test_1.h"

extern "C" {
    int LLVMFuzzerRunDriver(int *argc, char ***argv, int (*UserCb)(const uint8_t *data, size_t size));
};

struct ThreadArgs {
  int argc;
  char **argv;
};

void* wrapper(void *arg){

    ThreadArgs *args = static_cast<ThreadArgs*>(arg);
    LLVMFuzzerRunDriver(&args->argc, (char ***)&args->argv, &LLVMFuzzerTestOneInput);
} 

void UBSanFinding(const uint8_t *const message, size_t len)
{
    std::cout << "#####  Fuzz thread ID: " << pthread_self() << std::endl;
    if (len > 4)
    {
        if (message[0] == 'F')
        {
            if (message[1] == 'U')
            {
                if (message[2] == 'Z')
                {
                    if (message[3] == 'Z')
                    {
                        int x[3];
                        int y = 4;
                        int z = x[y];
                        printf("Z %d",z);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) { 
    std::cout << "Start Main Function" << std::endl;

    ThreadArgs args;
    args.argc = argc;
    args.argv = argv;

    // LLVMFuzzerRunDriver(&argc, &argv, &LLVMFuzzerTestOneInput);
    pthread_t thread; 
    pthread_create(&thread, NULL, wrapper, &args);

    while(1){
        for (int i = 0 ; i < 1e4; i++);
        std::cout << "#####  Main thread ID: " << pthread_self() << std::endl;
    }
    pthread_join(thread, NULL);
    return 0;
}
