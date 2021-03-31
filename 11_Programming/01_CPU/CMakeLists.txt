cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2 -std=c++11")

add_executable(bind_cpu bind_cpu.cpp)
target_link_libraries(bind_cpu pthread)

