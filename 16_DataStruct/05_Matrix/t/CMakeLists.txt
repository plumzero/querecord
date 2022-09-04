
cmake_minimum_required(VERSION 2.8)

project("matrix" C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -W -Wall -g -O2")

add_executable(symmetric_matrix   symmetric_matrix.c)
add_executable(triangular_matrix  triangular_matrix.c)
add_executable(diagonal_matrix    diagonal_matrix.c)
