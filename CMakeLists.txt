cmake_minimum_required(VERSION 3.19)
project(AUTOMOTIVE-FUZZING-EXAMPLE-CPP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

find_package(cifuzz)
enable_fuzz_testing()


add_library(TARGET_SUT
    modules/target.cpp
)

target_include_directories(TARGET_SUT PRIVATE
    modules/
)

add_fuzz_test(my_fuzz_test_1 fuzzing/my_fuzz_test_1.cpp)
target_include_directories(my_fuzz_test_1 PRIVATE
    modules/
)

target_link_libraries(my_fuzz_test_1 PRIVATE PRIVATE TARGET_SUT)
