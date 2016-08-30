cmake_minimum_required(VERSION 3.3)
project(milestone1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Task.cpp Task.h Utilities.cpp Utilities.h)
add_executable(milestone1 ${SOURCE_FILES})