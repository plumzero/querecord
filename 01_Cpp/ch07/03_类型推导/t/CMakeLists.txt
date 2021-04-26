
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11 -Wno-unused-variable")

add_executable(01_auto       01_auto.cpp)
add_executable(03_declval    03_declval.cpp)
