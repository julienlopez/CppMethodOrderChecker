cmake_minimum_required(VERSION 3.3)
project(LibMethodOrderChecker)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_library(LibMethodOrderChecker ${SOURCE_FILES})
