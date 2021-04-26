
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11 -Wno-unused-variable -Wno-unused-parameter -Wno-unused-local-typedefs")

add_executable(01_integral_constant    01_integral_constant.cpp)

add_executable(02_is_base_of           02_is_base_of.cpp)
add_executable(02_is_class             02_is_class.cpp)
add_executable(02_is_const             02_is_const.cpp)
add_executable(02_is_convertible       02_is_convertible.cpp)
add_executable(02_is_integral          02_is_integral.cpp)
add_executable(02_is_same              02_is_same.cpp)
add_executable(02_traits_modify        02_traits_modify.cpp)
add_executable(02_traits_unique_ptr    02_traits_unique_ptr.cpp)
add_executable(02_typetraits_decay     02_typetraits_decay.cpp)

add_executable(03_conditional          03_conditional.cpp)
add_executable(03_result_of            03_result_of.cpp)
add_executable(03_result_of2           03_result_of2.cpp)
add_executable(03_enable_if            03_enable_if.cpp)
