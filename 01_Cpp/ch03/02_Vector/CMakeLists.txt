
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_initialize           01_initialize.cpp)
add_executable(02_reserve              02_reserve.cpp)
add_executable(03_resize               03_resize.cpp)
add_executable(04_access               04_access.cpp)
add_executable(05_emplace              05_emplace.cpp)
add_executable(06_erase_remove         06_erase_remove.cpp)

