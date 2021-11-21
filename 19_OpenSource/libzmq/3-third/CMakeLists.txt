cmake_minimum_required(VERSION 2.8.0)

add_executable(client3 client3.cpp)
target_link_libraries(client3 ${zmq_LIBRARY_NAME})

add_executable(server3 server3.cpp)
target_link_libraries(server3 ${zmq_LIBRARY_NAME})


add_executable(_client3 _client3.cpp)
target_link_libraries(_client3 ${zmq_LIBRARY_NAME})

add_executable(_server3 _server3.cpp)
target_link_libraries(_server3 ${zmq_LIBRARY_NAME})

