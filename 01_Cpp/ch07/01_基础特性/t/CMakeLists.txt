
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -fno-elide-constructors -Wno-unused-but-set-variable -O2 -std=c++11")

add_executable(02_iterator_range           02_iterator_range.cpp)


# 可以尝试对该程序使用 -fno-elide-constructors 选项，比较
add_executable(08_emplace_back_diff         08_emplace_back_diff.cpp)
