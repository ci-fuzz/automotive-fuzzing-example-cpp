cmake_minimum_required(VERSION 3.16)
project(FUZZING-EXAMPLE-CPP)

find_package(cifuzz)
enable_fuzz_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_VERBOSE_MAKEFILE on )

##################### SUT fuzzing ####################################

set(FUZZING_COMPILE_FLAGS_Fuzzing
                            -g  # Generate debug information.
                            -Og
                            -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
                            -fsanitize=fuzzer
                            -fsanitize=address,undefined
                            -fprofile-instr-generate
                            -fsanitize-recover=address
                            -fsanitize-address-use-after-scope
                            -fno-sanitize=function,vptr
                            -fno-omit-frame-pointer
)

set(FUZZING_LINKER_FLAGS_Fuzzing
                            -fsanitize=fuzzer
                            -fsanitize=address,undefined
)

add_library(SUT_Fuzzing
    modules/target.cpp
)

target_include_directories(SUT_Fuzzing PRIVATE
    modules
)
target_compile_options(SUT_Fuzzing PRIVATE ${FUZZING_COMPILE_FLAGS_Fuzzing})
target_link_options(SUT_Fuzzing PRIVATE ${FUZZING_LINKER_FLAGS_Fuzzing})

##################### Fuzzing ####################################

add_executable(my_fuzz_test_fuzzing fuzzing/my_fuzz_test_1.cpp)

target_include_directories(my_fuzz_test_fuzzing PRIVATE
    modules
)
target_link_libraries(my_fuzz_test_fuzzing PRIVATE SUT_Fuzzing)

target_compile_options(my_fuzz_test_fuzzing PRIVATE ${FUZZING_COMPILE_FLAGS_Fuzzing})
target_link_options(my_fuzz_test_fuzzing PRIVATE ${FUZZING_LINKER_FLAGS_Fuzzing})


##################### SUT Coverage ####################################

set(FUZZING_COMPILE_FLAGS_Coverage
                            -g
                            -O0 # no optimization
                            -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION
                            -fsanitize=fuzzer
                            -fprofile-instr-generate
                            -fcoverage-mapping
)

set(FUZZING_LINKER_FLAGS_Coverage
                            -fsanitize=fuzzer
                            -fprofile-instr-generate
)

add_library(SUT_Coverage
    modules/target.cpp
)

target_include_directories(SUT_Coverage PRIVATE
    modules
)
target_compile_options(SUT_Coverage PRIVATE ${FUZZING_COMPILE_FLAGS_Coverage})
target_link_options(SUT_Coverage PRIVATE ${FUZZING_LINKER_FLAGS_Coverage})

##################### Coverage ####################################

add_executable(my_fuzz_test_coverage fuzzing/my_fuzz_test_1.cpp)

target_include_directories(my_fuzz_test_coverage PRIVATE
    modules
)
target_link_libraries(my_fuzz_test_coverage PRIVATE SUT_Coverage)

target_compile_options(my_fuzz_test_coverage PRIVATE ${FUZZING_COMPILE_FLAGS_Coverage})
target_link_options(my_fuzz_test_coverage PRIVATE ${FUZZING_LINKER_FLAGS_Coverage})



##################### SUT CLI ####################################

add_library(SUT_Cli
    modules/target.cpp
)

target_include_directories(SUT_Fuzzing PRIVATE
    modules
)

#set(CMAKE_BUILD_TYPE "Debug")

add_fuzz_test(my_fuzz_test_cli fuzzing/my_fuzz_test_1.cpp)

target_include_directories(my_fuzz_test_cli PRIVATE
    modules
)
target_link_libraries(my_fuzz_test_cli PRIVATE SUT_Cli)
