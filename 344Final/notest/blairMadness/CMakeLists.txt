cmake_minimum_required(VERSION 3.3)
project(w7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(w7 ${SOURCE_FILES})