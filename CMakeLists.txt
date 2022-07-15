cmake_minimum_required(VERSION 3.16)
project(AUTOMOTIVE-FUZZING-EXAMPLE-CPP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

find_package(cifuzz)
enable_fuzz_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(AUTOMOTIVE-FUZZING-EXAMPLE-CPP
    modules/crypto_module/src/crypto_module_1.cpp
    modules/crypto_module/src/crypto_module_2.cpp
    modules/time_module/src/time_module_1.cpp
    modules/GPS_module/src/GPS_module_1.cpp
    modules/key_management_module/src/key_management_module_1.cpp
)

target_include_directories(AUTOMOTIVE-FUZZING-EXAMPLE-CPP PRIVATE
    modules/crypto_module/src
    modules/time_module/src
    modules/key_management_module/src
    modules/GPS_module/src
)

add_executable(tests
    test/simple_unit_test.cpp   
)

target_include_directories(tests PRIVATE
    modules/crypto_module/src
    modules/time_module/src
    modules/key_management_module/src
    modules/GPS_module/src
)

target_link_libraries(tests PRIVATE GTest::gtest_main PRIVATE AUTOMOTIVE-FUZZING-EXAMPLE-CPP)

include(GoogleTest)
gtest_discover_tests(tests)

add_fuzz_test(my_fuzz_test_1 my_fuzz_test_1.cpp)
target_include_directories(my_fuzz_test_1 PRIVATE
    modules/crypto_module/src
    modules/time_module/src
    modules/key_management_module/src
    modules/GPS_module/src
)

target_link_libraries(my_fuzz_test_1 PRIVATE GTest::gtest_main PRIVATE AUTOMOTIVE-FUZZING-EXAMPLE-CPP)
