
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

add_subdirectory(1-function)
add_subdirectory(2-class)
add_subdirectory(3-ttp)
add_subdirectory(04_function_template_specialization)
add_subdirectory(5-function_wrapper)

