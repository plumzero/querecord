
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Wno-unused-but-set-variable -O2 -std=c++11")

add_executable(delegating_constructor          delegating_constructor.cpp)
add_executable(Inheritance_constructor         Inheritance_constructor.cpp)

