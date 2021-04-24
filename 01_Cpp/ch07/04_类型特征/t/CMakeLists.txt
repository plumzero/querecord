
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(01_integral_constant             01_integral_constant.cpp)

add_executable(is_base_of           is_base_of.cpp)
add_executable(is_class             is_class.cpp)
add_executable(is_const             is_const.cpp)
add_executable(is_convertible       is_convertible.cpp)
add_executable(is_integral          is_integral.cpp)
add_executable(is_same              is_same.cpp)
add_executable(traits_modify        traits_modify.cpp)
add_executable(traits_unique_ptr    traits_unique_ptr.cpp)
add_executable(typetraits_decay     typetraits_decay.cpp)

add_executable(std_conditional      std_conditional.cpp)
add_executable(std_result_of        std_result_of.cpp)
add_executable(std_result_of2       std_result_of2.cpp)
add_executable(traits_enable_if     traits_enable_if.cpp)
