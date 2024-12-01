#!/system/bin/sh
mkdir build
cd build
cmake ..
make && ./ogltest
