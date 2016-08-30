cmake_minimum_required(VERSION 3.3)
project(milestone3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CustomerOrder.cpp CustomerOrder.h Utilities.cpp Utilities.h Task.cpp Task.h Item.cpp Item.h ItemOrder.cpp ItemOrder.h TaskManager.cpp TaskManager.h ItemManager.cpp ItemManager.h OrderManager.cpp OrderManager.h)
add_executable(milestone3 ${SOURCE_FILES})