
cmake_minimum_required(VERSION 3.0.2)

add_executable(system_simple                  system_simple.cc)
add_executable(system_return                  system_return.cc)
add_executable(system_fork_waitpid            system_fork_waitpid.cc)
add_executable(fork_waitpid                   fork_waitpid.cc)

add_executable(exec                   exec.cc)
