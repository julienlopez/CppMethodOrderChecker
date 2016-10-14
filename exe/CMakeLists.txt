cmake_minimum_required(VERSION 3.3)
project(MethodOrderChecker)

include_directories(../lib)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(MethodOrderChecker ${SOURCE_FILES})

target_link_libraries(MethodOrderChecker LibMethodOrderChecker)
target_link_libraries(MethodOrderChecker boost_system-mt boost_filesystem-mt)
