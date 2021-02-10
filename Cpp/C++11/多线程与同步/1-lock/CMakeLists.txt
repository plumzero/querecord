cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(lock_guard      lock_guard.cpp)
target_link_libraries(lock_guard pthread)

add_executable(unique_lock     unique_lock.cpp)
target_link_libraries(unique_lock pthread)