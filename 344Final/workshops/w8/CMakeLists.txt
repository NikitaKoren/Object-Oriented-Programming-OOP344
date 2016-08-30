cmake_minimum_required(VERSION 3.3)
project(w8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DataTable.h)
add_executable(w8 ${SOURCE_FILES})