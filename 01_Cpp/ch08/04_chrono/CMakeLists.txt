
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(01_duration_arithmetic           01_duration_arithmetic.cpp)
add_executable(02_duration_convert              02_duration_convert.cpp)
add_executable(03_duration_compare              03_duration_compare.cpp)
add_executable(04_clock_is_steady               04_clock_is_steady.cpp)
add_executable(05_time_point_create             05_time_point_create.cpp)
add_executable(06_time_point_duration           06_time_point_duration.cpp)
add_executable(06_time_point_timediff           06_time_point_timediff.cpp)
add_executable(07_time_point_compare            07_time_point_compare.cpp)
add_executable(08_time_point_ctime              08_time_point_ctime.cpp)
add_executable(09_time_point_second             09_time_point_second.cpp)
