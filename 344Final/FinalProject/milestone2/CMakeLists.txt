cmake_minimum_required(VERSION 3.3)
project(milestone2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CustomerOrder.cpp CustomerOrder.h Utilities.cpp Utilities.h Task.cpp Task.h Item.cpp Item.h ItemOrder.cpp ItemOrder.h)
add_executable(milestone2 ${SOURCE_FILES})