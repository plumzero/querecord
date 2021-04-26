
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(01_deque_initialize          01_deque_initialize.cpp)
add_executable(02_deque_access              02_deque_access.cpp)
add_executable(03_deque_emplace             03_deque_emplace.cpp)
