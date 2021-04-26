
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -fno-elide-constructors -Wno-unused-but-set-variable -Wno-reorder -Wno-unused-variable -O2 -std=c++11")

add_executable(02_iterator_range            02_iterator_range.cpp)
add_executable(05_constexpr                 05_constexpr.cpp)
add_executable(06_enum_class                06_enum_class.cpp)
add_executable(07_delegating_constructor    07_delegating_constructor.cpp)
add_executable(07_inheritance_constructor   07_inheritance_constructor.cpp)

# 可以尝试对该程序使用 -fno-elide-constructors 选项，比较
add_executable(08_emplace_back_diff         08_emplace_back_diff.cpp)

add_executable(08_emplace_back_vec          08_emplace_back_vec.cpp)
add_executable(09_tuple                     09_tuple.cpp)
