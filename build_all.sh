#!/bin/sh
#cmake -DCMAKE_TOOLCHAIN_FILE="../armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug  .
#make -j4
export ARMGCC_DIR=/usr/local/gcc-arm-none-eabi-7-2018-q2-update
mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="../cmake/armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release  ../cmake
make -j4
