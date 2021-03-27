
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_subdirectory(1-bind1st和bind2nd)
add_subdirectory(2-bind_class_member)
add_subdirectory(3-bind_other)
add_subdirectory(4-callable_objects)
