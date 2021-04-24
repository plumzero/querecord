
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(01_async 01_async.cpp)
target_link_libraries(01_async pthread)

add_executable(01_async2sync 01_async2sync.cpp)
target_link_libraries(01_async2sync pthread)

add_executable(03_promise 03_promise.cpp)
target_link_libraries(03_promise pthread)

add_executable(04_packaged_task 04_packaged_task.cpp)
target_link_libraries(04_packaged_task pthread)
