cmake_minimum_required(VERSION 2.8.0)

add_executable(req_rep_client req_rep_client.cpp)
target_link_libraries(req_rep_client ${zmq_LIBRARY_NAME})

add_executable(req_rep_server req_rep_server.cpp)
target_link_libraries(req_rep_server ${zmq_LIBRARY_NAME})

