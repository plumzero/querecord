
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -fno-elide-constructors -Wno-unused-but-set-variable -Wno-reorder -Wno-unused-variable -O2 -std=c++11")


cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11 -Wno-unused-variable")

set(CMAKE_CXX_STANDARD 11)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(file ${files})
    get_filename_component(name ${file} NAME_WE)
    add_executable(${name} ${file})
endforeach()

# 可以尝试对 08_emplace_back_diff.cpp 使用 -fno-elide-constructors 选项，比较
