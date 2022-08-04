
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(02_hp_anon      02_hp_anon.cpp)
target_link_libraries(02_hp_anon rt)

add_executable(02_hp_fd      02_hp_fd.cpp)
target_link_libraries(02_hp_fd rt)

add_executable(02_hp_shared_anon      02_hp_shared_anon.cpp)
target_link_libraries(02_hp_shared_anon rt)

add_executable(02_hp_shared_fd      02_hp_shared_fd.cpp)
target_link_libraries(02_hp_shared_fd rt)

add_executable(02_hp_zero      02_hp_zero.cpp)
target_link_libraries(02_hp_zero rt)
