
cmake_minimum_required(VERSION 3.0.2)

project("Tools Learning" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01_random)
add_subdirectory(02_numeric)
add_subdirectory(03_valarray)
add_subdirectory(04_chrono)
