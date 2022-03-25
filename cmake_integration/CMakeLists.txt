if(DEFINED CIFUZZ_INSTALL_ROOT)
  
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CIFUZZ_INSTALL_ROOT}/share/cmake")

  find_package(CIFuzz)

  file(GLOB targets "fuzz_targets/*.cpp")
  foreach(fuzzer_source ${targets})

    get_filename_component(fuzzer ${fuzzer_source} NAME_WE)

    add_cifuzz_test(${fuzzer} AUTOMOTIVE-FUZZING-EXAMPLE-CPP
      SOURCES     ${fuzzer_source}
      MAX_RUNTIME "30m"
      PARALLEL_EXECUTIONS "1"
      SEED_CORPUS "${CMAKE_CURRENT_SOURCE_DIR}/seeds/${fuzzer}"
    )
    
    target_link_libraries(${fuzzer} PRIVATE AUTOMOTIVE-FUZZING-EXAMPLE-CPP)

    #cifuzz_test_link_libraries(${fuzzer} AUTOMOTIVE-FUZZING-EXAMPLE-CPP)
    
    target_include_directories(${fuzzer} PRIVATE 
    ../modules/crypto_module/src
    ../modules/time_module/src
    ../modules/key_management_module/src
    ../modules/GPS_module/src
    )

  endforeach()

endif()