cmake_minimum_required(VERSION 3.1)
project(Diplom)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    api.hpp
    dsk.cpp
    dsk.hpp)

add_executable(Diplom ${SOURCE_FILES})