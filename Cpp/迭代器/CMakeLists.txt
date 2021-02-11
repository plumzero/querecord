
cmake_minimum_required(VERSION 3.0.2)

project("iterator test" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01_iterator)
add_subdirectory(02_istream_iterator)
add_subdirectory(03_ostream_iterator)
