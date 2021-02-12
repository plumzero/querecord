cmake_minimum_required(VERSION 3.0.2)

project("Container" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01-resize)
add_subdirectory(02-push_back)
add_subdirectory(03-max_size)
add_subdirectory(04-list_remove)
add_subdirectory(05-list_sort)
add_subdirectory(06-initialize_list)
add_subdirectory(07-string_vec)
add_subdirectory(08-diff_12)
add_subdirectory(09-merge)
add_subdirectory(10-ring_list)
add_subdirectory(11-unordered_map)

