# automotive-fuzzing-example-cpp

Run: cifuzz run :my_fuzz_test_1

There are four multithreading examples.
0. the first one is without protection
1. the scound has a naive protection by waiting 1 secound
2. the third one wait until a thread terminated by using pthread_join()
3. the last one blocks threads by mutex

to use it comment and uncomment the function:
FUZZ_TEST(const uint8_t *data, size_t size) {

  start_thread0(data, size);
//  start_thread1(data, size);
//  start_thread2(data, size);
//  start_thread3(data, size);
}

Compare duration for solutions:

1. exec/s: 1 (36s)  // depends on std::this_thread::sleep_for(std::chrono::seconds(1));
2. exec/s: 206 (7s)   
3. exec/s: 64