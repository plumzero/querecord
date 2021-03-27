
cmake_minimum_required(VERSION 3.0.2)

file(COPY read.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01_from_stdin        01_from_stdin.cpp)
add_executable(02_read_int          02_read_int.cpp)
add_executable(03_read_char         03_read_char.cpp)
