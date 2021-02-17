cmake_minimum_required(VERSION 3.0.2)

project("Container test" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01_Array)
add_subdirectory(02_Vector)
add_subdirectory(03_Deque)
add_subdirectory(04_List)
