cmake_minimum_required(VERSION 3.10)
project(OpenGLTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES src/fileutils.c src/main.cpp src/glad.c)

# Add executable
add_executable(opengltest ${SOURCES})

# Link libraries
target_link_libraries(opengltest GL glfw)
