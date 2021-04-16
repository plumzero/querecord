
project(subdir)

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -O0 -Wall -W")

if (NOT CONF_PATH)
	set(CONF_PATH  "conf.ini")
endif()

if (NOT VERSION_MAJOR)
	set(VERSION_MAJOR 1)
endif()

if (NOT VERSION_MINOR)
	set(VERSION_MINOR 1)
endif()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/config.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(main main.cpp)
