#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <random>

#include "target.h"

#define FUZZ

struct ThreadArgs {
  const uint8_t * message;
  size_t len;
#ifdef FUZZ
  volatile int *finished;
  volatile int id;
#endif
};


void sleep(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int sleep_duration = dis(gen);

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
}


// #################### Solution 1 #####################################

void* UBSanFinding1(ThreadArgs& args) {

    sleep();

    std::cout << "#####  2 : Hello from thread! ID: " << std::this_thread::get_id() << std::endl;

    const uint8_t * const message = args.message;
    size_t len = args.len;

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
    return NULL;
}

void simpleExample(const uint8_t * const message, size_t len) {

    ThreadArgs args[num_threads];

    std::cout << "##### 1 : Create threads! " << std::endl;

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        args[i].message = message;
        args[i].len = len;

        threads[i] = std::thread(UBSanFinding1, std::ref(args[i]));
        threads[i].detach();
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}


volatile int threadFinished1[num_threads] = {0};
volatile int threadFinished2[num_threads] = {0};

void* UBSanFinding(ThreadArgs& args) {

    sleep();

    std::cout << "#####  THREAD : Hello from thread! ID: " << std::this_thread::get_id() << " <> " << args.id << std::endl;
    const uint8_t * const &message = args.message;
    size_t len = args.len;

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

#ifdef FUZZ
    *(args.finished) = 1;
    threadFinished2[args.id] = 1;
#endif

    return NULL;
}

void advancedExample(const uint8_t * const message, size_t len) {
  
    ThreadArgs args[num_threads];

    std::cout << "##### SUT : Create threads! " << std::endl;
    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        args[i].message = message;
        args[i].len = len;
#ifdef FUZZ
        args[i].finished = &threadFinished1[i];
        args[i].id = i;
        std::cout << "##### SUT : Start thread with id : " << args[i].id << std::endl;
#endif
        threads[i] = std::thread(UBSanFinding, std::ref(args[i]));
        threads[i].detach();
    }

    std::cout << "##### SUT : Has finished!" << std::endl;

}