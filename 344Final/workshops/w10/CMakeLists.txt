cmake_minimum_required(VERSION 3.3)
project(w10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SecureData.cpp SecureData.h)
add_executable(w10 ${SOURCE_FILES})