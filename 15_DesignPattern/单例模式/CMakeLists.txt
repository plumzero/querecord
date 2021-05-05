cmake_minimum_required(VERSION 3.0.2)

project("singleton" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -W")

add_executable(DoubleCheck DoubleCheck.cpp)
target_link_libraries(DoubleCheck pthread)

add_executable(NoCheck NoCheck.cpp)
target_link_libraries(NoCheck pthread)