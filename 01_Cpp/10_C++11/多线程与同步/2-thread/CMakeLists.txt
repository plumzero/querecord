cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -std=c++11 -g -O2 -Wall -W")

add_executable(thread_thread      thread_thread.cpp)
target_link_libraries(thread_thread pthread)

add_executable(thread_join     thread_join.cpp)
target_link_libraries(thread_join pthread)

add_executable(thread_joinable     thread_joinable.cpp)
target_link_libraries(thread_joinable pthread)

add_executable(thread_detach     thread_detach.cpp)
target_link_libraries(thread_detach pthread)
