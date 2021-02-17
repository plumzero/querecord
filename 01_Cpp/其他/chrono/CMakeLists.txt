
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_subdirectory(01-count)
add_subdirectory(02-time_point)
add_subdirectory(03-clocks)
