
cmake_minimum_required(VERSION 3.0.2)

file(COPY srcfile DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01_write_int             01_write_int.cpp)
add_executable(02_copy_file_to_file     02_copy_file_to_file.cpp)
