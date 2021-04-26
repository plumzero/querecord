
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2 -std=c++11")

add_executable(02_callable_objects             02_callable_objects.cpp)
add_executable(02_functional_callable_objects  02_functional_callable_objects.cpp)
add_executable(02_functional_callback          02_functional_callback.cpp)


add_executable(03_bind_class_member            03_bind_class_member.cpp)
add_executable(03_bind_placeholders            03_bind_placeholders.cpp)

add_executable(03_bind1st                      03_bind1st.cpp)
add_executable(03_bind2nd                      03_bind2nd.cpp)
