cmake_minimum_required(VERSION 3.1)
set(PROJECT Diplom)
project(${PROJECT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Wno-deprecated")

set(HEADERS_FILES
    api.hpp
    dsk.hpp)
set(SOURCE_FILES
    api.hpp
    dsk.hpp
    dsk.cpp)

add_executable(Diplom ${HEADERS_FILES} ${SOURCE_FILES})