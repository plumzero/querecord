cmake_minimum_required(VERSION 3.0.2)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W -Wno-unused-parameter -Wno-unused-variable -Wno-unused-parameter")

add_executable(03_reference                             03_reference.cpp)
add_executable(04_base_pointer_virtual_inherit          04_base_pointer_virtual_inherit.cpp)
add_executable(04_base_pointer                          04_base_pointer.cpp)
add_executable(04_inherit_construct                     04_inherit_construct.cpp)
add_executable(05_friend_class                          05_friend_class.cpp)
add_executable(05_friend_func                           05_friend_func.cpp)
add_executable(07_construct                             07_construct.cpp)
add_executable(09_virtual_member_func                   09_virtual_member_func.cpp)
add_executable(11_class_implict                         11_class_implict.cpp)
add_executable(11_dynamic_cast                          11_dynamic_cast.cpp)
add_executable(12_typeid                                12_typeid.cpp)
add_executable(12_typeinfo                              12_typeinfo.cpp)
add_executable(14_exception                             14_exception.cpp)