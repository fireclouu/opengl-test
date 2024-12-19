cmake_minimum_required(VERSION 3.10)
project(opengl-test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
# Include directories
include_directories(include)

# Source files
set(SOURCES src/glad/glad.c src/utils/file_utils.cpp src/utils/opengl_utils.cpp)

# put sahders file together with build folders
set(SHADERS_SRC_DIR ${CMAKE_SOURCE_DIR}/src/shaders)
set(SHADERS_DEST_DIR ${CMAKE_BINARY_DIR}/bin/shaders)
set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/bin/assets)
file(MAKE_DIRECTORY ${SHADERS_DEST_DIR})
file(MAKE_DIRECTORY ${ASSETS_DEST_DIR}/textures)

# Add executable
file(GLOB exercise_sources "src/exercise-*.cpp")
foreach(source_file IN LISTS exercise_sources)
  get_filename_component(binary_name ${source_file} NAME_WE)
  add_executable(${binary_name} ${SOURCES} ${source_file})
  target_link_libraries(${binary_name} GL glfw)
endforeach()

add_custom_target(copy_shaders ALL COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${SHADERS_SRC_DIR}/* ${SHADERS_DEST_DIR}/
)

add_custom_target(copy_asset_textures ALL COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${ASSETS_SRC_DIR}/textures/* ${ASSETS_DEST_DIR}/textures/
)
