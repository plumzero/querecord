
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_initialize          01_initialize.cpp)
add_executable(02_access              02_access.cpp)
add_executable(03_emplace             03_emplace.cpp)
