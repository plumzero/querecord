
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

add_executable(class_args     class_args.cpp)
add_executable(class_args2    class_args2.cpp)
add_executable(summator       summator.cpp)
add_executable(tuple          tuple.cpp)
