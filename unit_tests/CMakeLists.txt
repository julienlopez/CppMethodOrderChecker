cmake_minimum_required(VERSION 3.3)
project(unit_tests)

include_directories(../lib)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(unit_tests ${SOURCE_FILES})

target_link_libraries(unit_tests LibMethodOrderChecker)
target_link_libraries(unit_tests boost_system-mt boost_filesystem-mt)

target_link_libraries(unit_tests gtest pthread)
