cmake_minimum_required(VERSION 3.0.2)

project("Container test" CXX)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -W")

add_subdirectory(01_Array)
add_subdirectory(02_Vector)
add_subdirectory(03_Deque)
add_subdirectory(04_List)
add_subdirectory(05_Forward_list)

add_subdirectory(06_Stack)
add_subdirectory(07_Queue)
add_subdirectory(08_Priority_queue)

add_subdirectory(09_String)

add_subdirectory(10_SC_Heap)
add_subdirectory(10_SC_RelationalOperators)
add_subdirectory(10_SC_SmartPointer)

add_subdirectory(11_Map)
add_subdirectory(12_Multimap)
add_subdirectory(13_Unordered_map)

add_subdirectory(17_RC_KeyCompare)

add_subdirectory(18_Tuple)
