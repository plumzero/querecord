
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -fno-elide-constructors -O2 -std=c++11")

add_executable(emplace_back_vec           emplace_back_vec.cpp)
add_executable(emplace_back_diff          emplace_back_diff.cpp)

