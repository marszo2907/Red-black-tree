cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)

project(RedBlackTreeDemo)

add_executable(${PROJECT_NAME} src/RedBlackTreeDemo.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)