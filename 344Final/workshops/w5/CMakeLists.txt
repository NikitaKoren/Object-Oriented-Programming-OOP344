cmake_minimum_required(VERSION 3.3)
project(w5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES w5.cpp Notifications.cpp Notifications.h Message.cpp Message.h)
add_executable(w5 ${SOURCE_FILES} Notifications.cpp Notifications.h Message.cpp Message.h)