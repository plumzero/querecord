
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11 -Wno-unused-parameter")

add_executable(01_move_copy         01_move_copy.cpp)
add_executable(01_rvalue            01_rvalue.cpp)
add_executable(02_move_vector       02_move_vector.cpp)
