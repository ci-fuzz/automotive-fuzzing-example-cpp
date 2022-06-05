set -e
mkdir -p build
cd build
cmake .. # Here, you can place your CMake options such as -DDISABLE_TESTS
make -j$(nproc)