#!/system/bin/sh
BUILD_NAME="opengltest"
mkdir build && rm $BUILD_NAME
cd build
cmake ..
make && ./$BUILD_NAME
