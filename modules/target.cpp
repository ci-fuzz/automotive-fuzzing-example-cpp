#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "target.h"

struct ThreadArgs {
  const uint8_t * const message;
  size_t len;
};

const int num_threads = 5;

void sleep(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int sleep_duration = dis(gen);

    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
}

void* hmac0(void* arg) {

    sleep();

    std::cout << "#####  2 : Hello from thread! ID: " << pthread_self() << std::endl;

    ThreadArgs* args = static_cast<ThreadArgs*>(arg);
    const uint8_t * const message = args->message;
    size_t len = args->len;

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

void start_thread0(const uint8_t * const message, size_t len) {
  
    ThreadArgs args = {message, len};
    std::cout << "##### 1 : Create thread! Solution 1" << std::endl;

    const int num_threads = 5;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], NULL, hmac0, &args);
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}

void* hmac1(void* arg) {

    sleep();

    std::cout << "#####  2 : Hello from thread! ID: " << pthread_self() << std::endl;

    ThreadArgs* args = static_cast<ThreadArgs*>(arg);
    const uint8_t * const message = args->message;
    size_t len = args->len;

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

    const int num_threads = 5;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], NULL, hmac1, &args);
    }

    // solution 1
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}

void* hmac2(void* arg) {

    sleep();

    std::cout << "#####  2 : Hello from thread! ID: " << pthread_self() << std::endl;

    ThreadArgs* args = static_cast<ThreadArgs*>(arg);
    const uint8_t * const message = args->message;
    size_t len = args->len;

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

    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], NULL, hmac2, &args);
    }

    // solution 2
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}



pthread_cond_t cond;
pthread_mutex_t mutex;
bool flags[num_threads];


void* hmac3(void* arg) {
    pthread_mutex_lock(&mutex);
    
    sleep();

    std::cout << "#####  2 : Hello from thread! ID: " << pthread_self() << std::endl;

    ThreadArgs* args = static_cast<ThreadArgs*>(arg);
    const uint8_t * const message = args->message;
    size_t len = args->len;

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
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void start_thread3(const uint8_t * const message, size_t len) {
  
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    ThreadArgs args = {message, len};
    std::cout << "##### 1 : Create thread! Solution 3" << std::endl;

    const int num_threads = 5;
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], NULL, hmac3, &args);
    }

    std::cout << "##### 3 : Thread has finished!" << std::endl;

}

