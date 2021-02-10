cmake_minimum_required(VERSION 2.8)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

set(GCC_VERSION ${CMAKE_C_COMPILER_VERSION})
if(GCC_VERSION VERSION_LESS 4.9)
    message(FATAL_ERROR "GCC version too low ${GCC_VERSION}")
    return()
endif()

add_executable(basic_regex    basic_regex.cpp)
add_executable(sub_match      sub_match.cpp)
add_executable(regex_search   regex_search.cpp)
