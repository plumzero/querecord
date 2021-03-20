
cmake_minimum_required(VERSION 3.0.2)

file(COPY word.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01_stream_struct                  01_stream_struct.cpp)
add_executable(02_find                           02_find.cpp)
add_executable(03_count_if                       03_count_if.cpp)
add_executable(04_for_each                       04_for_each.cpp)
add_executable(05_generate_n                     05_generate_n.cpp)
