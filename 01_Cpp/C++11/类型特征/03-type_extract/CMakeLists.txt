
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(std_conditional      std_conditional.cpp)
add_executable(std_result_of        std_result_of.cpp)
add_executable(std_result_of2       std_result_of2.cpp)
add_executable(traits_enable_if     traits_enable_if.cpp)
