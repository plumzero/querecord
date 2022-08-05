
cmake_minimum_required(VERSION 3.0.2)

project("iterator test" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01_iterator)
add_subdirectory(02_istream_iterator)
add_subdirectory(03_ostream_iterator)
add_subdirectory(04_stream_more)
add_subdirectory(05_streambuf_iterator)
add_subdirectory(06_reverse_iterator)
add_subdirectory(07_iterator_func)
add_subdirectory(08_allocator)
