
cmake_minimum_required(VERSION 3.5)
project("callable test" CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra")

add_executable(hello_test           hello_test.cpp)
add_executable(hello_func           hello_func.cpp)
add_executable(hello_cls            hello_cls.cpp)
add_executable(hello_bind_string    hello_bind_string.cpp)
add_executable(hello_bind_tmpl      hello_bind_tmpl.cpp)
add_executable(hello_bind_tmpl_ex   hello_bind_tmpl_ex.cpp)
add_executable(hello_bind_macro     hello_bind_macro.cpp)