# automotive-fuzzing-example-cpp

Run: cifuzz run :my_fuzz_test_1

There are four multithreading examples.
1. the scound has a naive protection by waiting 1 secound and the threads are detached
2. the third one wait until a thread terminated by using join() and lock_guard
3. the third one wait until a thread terminated by using join() and unique_lock

to use it comment and uncomment the function:
FUZZ_TEST(const uint8_t *data, size_t size) {

  start_thread1(data, size);
//  start_thread2(data, size);
//  start_thread3(data, size);
}

Compare duration for solutions:

1. exec/s: 1 (53s) // depends on std::this_thread::sleep_for(std::chrono::seconds(1));
2. exec/s: 36 (23s) 
3. exec/s: 36 (24s) 