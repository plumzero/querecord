cmake_minimum_required(VERSION 2.8.0)

add_executable(simpleclient simpleclient.cpp)
target_link_libraries(simpleclient ${zmq_LIBRARY_NAME})

add_executable(simpleserver simpleserver.cpp)
target_link_libraries(simpleserver ${zmq_LIBRARY_NAME})

