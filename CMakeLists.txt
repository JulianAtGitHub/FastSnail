cmake_minimum_required(VERSION 3.2)
project(FastSnail)

include_directories(".")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Test.cpp FastSnail.cpp Base/FSAllocator.cpp Base/FSObject.cpp Structure/FSArray.cpp Structure/FSList.cpp)
add_executable(FastSnail ${SOURCE_FILES})