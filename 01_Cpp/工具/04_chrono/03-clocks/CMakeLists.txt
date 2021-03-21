
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(high_resolution_clock     high_resolution_clock.cpp)
add_executable(timer                     timer.cpp)

