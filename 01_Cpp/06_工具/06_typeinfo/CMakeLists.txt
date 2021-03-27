cmake_minimum_required(VERSION 3.0.2)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_executable(01_typeid        01_typeid.cpp)
add_executable(02_typeinfo      02_typeinfo.cpp)
