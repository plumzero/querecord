
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Wno-unused-but-set-variable -O2 -std=c++11")

add_executable(rvalue             rvalue.cpp)
add_executable(ur                 ur.cpp)
add_executable(move_copy          move_copy.cpp)

