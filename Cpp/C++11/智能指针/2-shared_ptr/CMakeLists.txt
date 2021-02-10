cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(sp_use_count      sp_use_count.cpp)
add_executable(sp_construct      sp_construct.cpp)
add_executable(sp_reset          sp_reset.cpp)
add_executable(sp_deleter        sp_deleter.cpp)

