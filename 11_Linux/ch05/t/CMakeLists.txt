
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(02_hugepage      02_hugepage.cpp)
target_link_libraries(02_hugepage rt)
