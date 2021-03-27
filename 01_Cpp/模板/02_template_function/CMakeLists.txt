
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(01_specialization        01_specialization.cpp)
add_executable(02_func_wrapper          02_func_wrapper.cpp)
