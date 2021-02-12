
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(callable_objects             callable_objects.cpp)
add_executable(functional_callable_objects  functional_callable_objects.cpp)
add_executable(functional_callback          functional_callback.cpp)
