
cmake_minimum_required(VERSION 2.8)

project("p" C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W    \
                -Wno-unused-but-set-variable    \
                -Wno-maybe-uninitialized        \
                -Wno-unused-variable            \
                -g -O2")

add_executable(bisection        bisection.c)
add_executable(regula_falsi     regula_falsi.c)
add_executable(inverse_quad     inverse_quad.c)

add_executable(gss              gss.c)
add_executable(fibonacci        fibonacci.c)

add_executable(nelder_mead      nelder_mead.c)
