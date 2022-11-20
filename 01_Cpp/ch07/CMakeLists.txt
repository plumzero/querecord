
cmake_minimum_required(VERSION 2.8)

project("C++11 test" CXX)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/0*")
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_subdirectory(${name})
endforeach()
