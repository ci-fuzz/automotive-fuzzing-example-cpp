# automotive-fuzzing-example-cpp

Link: https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-presets.md#enable-cmakepresetsjson-in-the-cmake-tools-extension

Example has four presets.\
Create a project\
cmake -S . --preset={clang, gcc, cifuzz_run, cifuzz_coverage}

Build project\
cmake --build --preset={build_clang, build_gcc, build_cifuzz_run, build_cifuzz_coverage}

Fuzztests can be started (and fuzzing artifacts created) using the cifuzz_wrapper.sh script:
cifuzz {run, coverage, bundle}
