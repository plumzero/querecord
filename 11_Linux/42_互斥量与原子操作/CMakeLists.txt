
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

add_executable(atomic     atomic.c)

add_executable(rwlock      rwlock.c)
target_link_directories(rwlock -lpthread)

add_executable(etest     etest.cpp)
target_link_directories(etest -lpthread)
