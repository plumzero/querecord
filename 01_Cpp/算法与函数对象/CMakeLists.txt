
cmake_minimum_required(VERSION 3.0.2)

project("Container Algorithm" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(04_容器算法)
add_subdirectory(05_容器算法)
add_subdirectory(06_容器算法)
