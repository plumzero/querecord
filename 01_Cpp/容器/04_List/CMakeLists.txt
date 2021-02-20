
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_initialize           01_initialize.cpp)
add_executable(02_emplace              02_emplace.cpp)
add_executable(03_remove               03_remove.cpp)
add_executable(04_unique               04_unique.cpp)
add_executable(05_sort                 05_sort.cpp)
add_executable(06_merge                06_merge.cpp)
add_executable(07_splice               07_splice.cpp)
