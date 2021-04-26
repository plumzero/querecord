
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(01_iota                      01_iota.cpp)
add_executable(02_accumulate                02_accumulate.cpp)
add_executable(03_inner_product             03_inner_product.cpp)
add_executable(04_adjacent_difference       04_adjacent_difference.cpp)
add_executable(05_partial_sum               05_partial_sum.cpp)
add_executable(06_minmax_element            06_minmax_element.cpp)
