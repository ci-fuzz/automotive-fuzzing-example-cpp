#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <random>

#include "target.h"

struct ThreadArgs {
  const uint8_t * const message;
  size_t len;
  int id;
};

const int num_threads = 5;

void sleep(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int sleep_duration = dis(gen);

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
}


// #################### Solution 1 #####################################

void* hmac1(ThreadArgs& args) {

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

void start_thread1(const uint8_t * const message, size_t len) {
  
    ThreadArgs args = {message, len};
    std::cout << "##### 1 : Create thread! Solution 1" << std::endl;

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(hmac1, std::ref(args));
        threads[i].detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}

// #################### Solution 2 #####################################

std::mutex counter_mutex;

void* hmac2(ThreadArgs& args) {
    std::lock_guard<std::mutex> lock(counter_mutex);
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

void start_thread2(const uint8_t * const message, size_t len) {
  
    ThreadArgs args = {message, len};
    std::cout << "##### 1 : Create thread! Solution 2" << std::endl;

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(hmac2, std::ref(args));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}


// #################### Solution 3 #####################################

void* hmac3(ThreadArgs& args) {

    std::unique_lock<std::mutex> lock(counter_mutex);

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
    lock.unlock();
    return NULL;
}

void start_thread3(const uint8_t * const message, size_t len) {
  
    ThreadArgs args = {message, len};
    std::cout << "##### 1 : Create thread! Solution 3" << std::endl;

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(hmac4, std::ref(args));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}
