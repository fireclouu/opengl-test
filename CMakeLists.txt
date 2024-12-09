cmake_minimum_required(VERSION 3.10)
project(opengl-test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
# Include directories
include_directories(include)

# Source files
set(SOURCES src/glad.c)

# put sahders file together with build folders
set(SHADERS_SRC_DIR ${CMAKE_SOURCE_DIR}/src/shaders)
set(SHADERS_DEST_DIR ${CMAKE_BINARY_DIR}/bin/shaders)
file(MAKE_DIRECTORY ${SHADERS_DEST_DIR})

# Add executable
add_executable(exer-1-basic ${SOURCES} src/main.cpp)

# Link libraries
target_link_libraries(exer-1-basic GL glfw)

add_custom_target(copy_shaders ALL COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADERS_SRC_DIR}/* ${SHADERS_DEST_DIR}/
)
