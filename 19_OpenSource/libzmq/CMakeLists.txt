cmake_minimum_required(VERSION 2.8.0)

project("ZMQ Test" C CXX)

option(BUILD_1_FIRST_TEST     "Build 1-first program"    ON)
option(BUILD_2_SECOND_TEST    "Build 2-second program"   ON)
option(BUILD_3_THIRD_TEST     "Build 3-third program"    ON)

#
# if u wanna release, do like this `cmake -DCMAKE_BUILD_TYPE=Release`
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(CheckCXXCompilerFlag)

#
# Configuration
#
include("${PROJECT_SOURCE_DIR}/cmake/configuration.cmake")

#
# Dependencies
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

#
# Package
#
find_package(zmq REQUIRED)
include_directories(SYSTEM ${zmq_INCLUDE})
get_filename_component(zmq_LIBRARY_PATH ${zmq_LIBRARY} PATH)
get_filename_component(zmq_LIBRARY_NAME ${zmq_LIBRARY} NAME_WE)
string(REGEX REPLACE "^lib" "" zmq_LIBRARY_NAME ${zmq_LIBRARY_NAME})

link_directories(${zmq_LIBRARY_PATH})

#
# "zmq.hpp" Support
#
find_package(zmqhpp REQUIRED)
include_directories(SYSTEM ${zmqhpp_INCLUDE})
if(ZMQHPP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

#
# Test in Sub Directories
#
if(BUILD_1_FIRST_TEST)
    add_subdirectory(1-first)
endif()

if(BUILD_2_SECOND_TEST)
    add_subdirectory(2-second)
endif()

if(BUILD_3_THIRD_TEST)
    add_subdirectory(3-third)
endif()

#
# End
#
