
cmake_minimum_required(VERSION 3.0.2)

project("iterator" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_executable(iterator            iterator.cpp)
add_executable(istream_iterator    istream_iterator.cpp)
add_executable(ostream_iterator    ostream_iterator.cpp)
