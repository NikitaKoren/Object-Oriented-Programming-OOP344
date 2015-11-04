cmake_minimum_required(VERSION 3.3)
project(w6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Grades.h)
add_executable(w6 ${SOURCE_FILES})