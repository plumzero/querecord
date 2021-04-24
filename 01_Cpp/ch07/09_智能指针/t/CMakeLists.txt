cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(01_up_construct      01_up_construct.cpp)
add_executable(01_up_release        01_up_release.cpp)
add_executable(01_up_reset          01_up_reset.cpp)
add_executable(01_up_deleter        01_up_deleter.cpp)
add_executable(01_make_unique       01_make_unique.cpp)
add_executable(01_up_resource       01_up_resource.cpp)


add_executable(02_sp_use_count      02_sp_use_count.cpp)
add_executable(02_sp_construct      02_sp_construct.cpp)
add_executable(02_sp_reset          02_sp_reset.cpp)
add_executable(02_sp_deleter        02_sp_deleter.cpp)

add_executable(02_circular_reference      02_circular_reference.cpp)
