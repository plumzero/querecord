
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wextra -W")

add_executable(01_brk_sbrk              t/01_brk_sbrk.c)
add_executable(02_free_and_sbrk         t/02_free_and_sbrk.c)
