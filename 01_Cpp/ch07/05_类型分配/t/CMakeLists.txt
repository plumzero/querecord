
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Wno-reorder -O2 -std=c++11")

add_executable(01_aligned_storage     01_aligned_storage.cpp)

add_executable(02_easy                02_easy.cpp)
add_executable(02_feature             02_feature.cpp)
add_executable(02_deprecated          02_deprecated.cpp)
add_executable(02_complicated         02_complicated.cpp)
