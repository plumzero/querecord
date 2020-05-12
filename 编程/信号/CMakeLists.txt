cmake_minimum_required(VERSION 3.0.2)

project("signal" C CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_executable(sigdaemon    sigdaemon.cpp)
target_link_libraries(sigdaemon pthread)

add_executable(sigexit      sigexit.cpp)
target_link_libraries(sigexit pthread)

add_executable(sighup       sighup.cpp)
target_link_libraries(sighup pthread)

add_executable(sigkill      sigkill.cpp)
target_link_libraries(sigkill pthread)

add_executable(sigset_init  sigset_init.cpp)
target_link_libraries(sigset_init pthread)

add_executable(sigwait      sigwait.cpp)
target_link_libraries(sigwait pthread)