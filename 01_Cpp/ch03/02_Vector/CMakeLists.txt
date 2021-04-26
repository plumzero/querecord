
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_vector_initialize           01_vector_initialize.cpp)
add_executable(02_vector_reserve              02_vector_reserve.cpp)
add_executable(03_vector_resize               03_vector_resize.cpp)
add_executable(04_vector_access               04_vector_access.cpp)
add_executable(05_vector_emplace              05_vector_emplace.cpp)
add_executable(06_erase_remove                06_erase_remove.cpp)

