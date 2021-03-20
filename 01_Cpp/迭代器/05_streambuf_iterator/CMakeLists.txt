
cmake_minimum_required(VERSION 3.0.2)

file(COPY read.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY srcfile DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01_read_bytes            01_read_bytes.cpp)
add_executable(02_write_bytes           02_write_bytes.cpp)
add_executable(03_copy_file_to_file     03_copy_file_to_file.cpp)
