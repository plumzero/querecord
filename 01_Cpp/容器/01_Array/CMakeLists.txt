
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_initialize          01_initialize.cpp)
add_executable(02_access              02_access.cpp)
add_executable(03_empty               03_empty.cpp)
add_executable(04_get_n               04_get_n.cpp)
add_executable(05_iterator            05_iterator.cpp)
add_executable(06_compare             06_compare.cpp)
