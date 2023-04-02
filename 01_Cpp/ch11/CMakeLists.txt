
cmake_minimum_required(VERSION 2.8)

project("single test" CXX)

add_subdirectory(01_nolocker)
add_subdirectory(02_ring)
add_subdirectory(03_switch)
add_subdirectory(04_timer)
add_subdirectory(05_dag)
