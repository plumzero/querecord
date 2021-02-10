
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(packaged_task packaged_task.cpp)
target_link_libraries(packaged_task pthread)
