cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

set(GCC_VERSION ${CMAKE_C_COMPILER_VERSION})
if(GCC_VERSION VERSION_LESS 4.9)
    message(WARNING "GCC version too low ${GCC_VERSION}")
    return()
else()
    set(CMAKE_CXX_STANDARD 11)

    file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    foreach(file ${files})
        get_filename_component(name ${file} NAME_WE)
        add_executable(${name} ${file})
    endforeach()
endif()
