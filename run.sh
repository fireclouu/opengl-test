#!/system/bin/sh
BUILD_NAME="opengltest"

mkdir build 2> /dev/null && rm $BUILD_NAME 2> /dev/null
cd build
cmake ..
make && ./$BUILD_NAME
