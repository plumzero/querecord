
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

add_executable(count_args     count_args.cpp)
add_executable(func_args      func_args.cpp)
add_executable(custom_hash    custom_hash.cpp)
