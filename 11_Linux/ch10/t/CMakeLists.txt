
cmake_minimum_required(VERSION 2.8.0)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

#
# 依赖
#

find_library(protobuf_LIBRARY protobuf HINTS "/usr/local/protobuf/lib")

find_path(protobuf_INCLUDE google/protobuf/message.h HINTS "/usr/local/protobuf/include")

if(protobuf_LIBRARY AND protobuf_INCLUDE)
    set(PROTOBUF_FOUND TRUE)
    
    message(STATUS "${Green}Found protobuf library at: ${protobuf_LIBRARY}${Reset}")
    message(STATUS "${Green}Found protobuf include at: ${protobuf_INCLUDE}${Reset}")
else()
    message(FATAL_ERROR "${Red}Failed to locate protobuf dependency.${Reset}")
endif()

include_directories(${protobuf_INCLUDE})
get_filename_component(protobuf_LIBRARY_PATH ${protobuf_LIBRARY} PATH)
get_filename_component(protobuf_LIBRARY_NAME ${protobuf_LIBRARY} NAME_WE)
string(REGEX REPLACE "^lib" "" protobuf_LIBRARY_NAME ${protobuf_LIBRARY_NAME})

link_directories(${protobuf_LIBRARY_PATH})

include_directories(.)

#
# 使用
#
add_executable(02_hp_anon      02_hp_anon.cpp)
target_link_libraries(02_hp_anon rt)

add_executable(02_hp_fd      02_hp_fd.cpp)
target_link_libraries(02_hp_fd rt)

add_executable(02_hp_shared_anon      02_hp_shared_anon.cpp)
target_link_libraries(02_hp_shared_anon rt)

add_executable(02_hp_shared_fd      02_hp_shared_fd.cpp)
target_link_libraries(02_hp_shared_fd rt)

add_executable(02_hp_zero      02_hp_zero.cpp)
target_link_libraries(02_hp_zero rt)

#
# 向量
#
add_executable(03_simple      03_simple.cpp)
target_link_libraries(03_simple rt)

#
# 测试
#
# protoc --cpp_out=. struct.proto
#
add_executable(04_try_pod      04_try_pod.cpp)
target_link_libraries(04_try_pod rt)

add_executable(04_try_proto      04_try_proto.cpp  struct.pb.cc)
target_link_libraries(04_try_proto rt ${protobuf_LIBRARY_NAME} pthread)