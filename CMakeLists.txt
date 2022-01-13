cmake_minimum_required(VERSION 3.8)
project(DataStructures_Algorithms)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive -Wno-deprecated-declarations -m64 -fexceptions -g -fPIC -g -Wall -Wno-long-long -Wconversion -Wwrite-strings -Wsign-compare")

set(CMAKE_C_STANDAR 99)
set(CMAKE_CXX_STANDAR 11)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(src)

add_subdirectory(src)