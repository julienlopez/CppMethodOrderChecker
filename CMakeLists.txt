cmake_minimum_required(VERSION 3.3)
project(MethodOrderChecker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(lib)
add_subdirectory(unit_tests)
add_subdirectory(exe)
