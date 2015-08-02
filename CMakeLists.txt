cmake_minimum_required(VERSION 3.2)
project(FastSnail)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.c)
add_executable(FastSnail ${SOURCE_FILES} Base/FSObject.c)