cmake_minimum_required(VERSION 2.8.0)

#
# protoc --cpp_out=. arenatest.proto
#

include_directories(.)

add_executable(testThirteenth testThirteenth.cpp arenatest.pb.cc)
target_link_libraries(testThirteenth ${protobuf_LIBRARY_NAME})