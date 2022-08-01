
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(04_thread_local_storage      04_thread_local_storage.cc)
target_link_libraries(04_thread_local_storage pthread)
