
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

file(COPY data.cad DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01_cad2json           01_cad2json.cpp)

