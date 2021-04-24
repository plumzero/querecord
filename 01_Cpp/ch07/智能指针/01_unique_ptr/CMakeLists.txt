cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(up_construct      up_construct.cpp)
add_executable(up_release        up_release.cpp)
add_executable(up_reset          up_reset.cpp)
add_executable(up_deleter        up_deleter.cpp)
add_executable(make_unique       make_unique.cpp)
add_executable(up_resource       up_resource.cpp)
