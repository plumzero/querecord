cmake_minimum_required(VERSION 3.0.2)

project("foggy-seeking" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W -Wno-reorder")

add_executable(move_thread             move_thread.cpp)
target_link_libraries(move_thread pthread)

add_executable(new_thread              new_thread.cpp)
target_link_libraries(new_thread pthread)
