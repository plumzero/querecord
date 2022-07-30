
cmake_minimum_required(VERSION 2.8.0)

add_executable(pub_1 pub_1.cpp)
target_link_libraries(pub_1 ${zmq_LIBRARY_NAME})

add_executable(sub_1 sub_1.cpp)
target_link_libraries(sub_1 ${zmq_LIBRARY_NAME})
