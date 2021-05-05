
cmake_minimum_required(VERSION 3.0.2)

project("Optimization Effort" CXX C)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

include_directories(c_00)

add_subdirectory(t_01)
