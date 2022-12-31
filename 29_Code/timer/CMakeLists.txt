cmake_minimum_required(VERSION 3.0.2)

include(CheckCXXCompilerFlag)

include_directories(.)

set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W -Wno-unused-parameter -Wno-unused-variable -Wno-unused-parameter")

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})
    target_link_libraries(${name} -lrt -lpthread)
endforeach()
