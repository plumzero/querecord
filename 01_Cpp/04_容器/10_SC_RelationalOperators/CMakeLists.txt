
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format")

add_executable(RO_array           RO_array.cpp)
add_executable(RO_vector          RO_vector.cpp)
add_executable(RO_deque           RO_deque.cpp)
add_executable(RO_list            RO_list.cpp)
add_executable(RO_forward_list    RO_forward_list.cpp)
