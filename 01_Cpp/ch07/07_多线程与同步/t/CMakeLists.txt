
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(01_thread_create      01_thread_create.cpp)
target_link_libraries(01_thread_create pthread)

add_executable(01_thread_join     01_thread_join.cpp)
target_link_libraries(01_thread_join pthread)

add_executable(01_thread_joinable     01_thread_joinable.cpp)
target_link_libraries(01_thread_joinable pthread)

add_executable(01_thread_detach     01_thread_detach.cpp)
target_link_libraries(01_thread_detach pthread)

add_executable(02_lock_guard     02_lock_guard.cpp)
target_link_libraries(02_lock_guard pthread)

add_executable(02_unique_lock     02_unique_lock.cpp)
target_link_libraries(02_unique_lock pthread)

add_executable(04_atomic     04_atomic.cpp)
target_link_libraries(04_atomic pthread)