cmake_minimum_required(VERSION 3.3)
project(threads_debuging)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(threads_debuging ${SOURCE_FILES})