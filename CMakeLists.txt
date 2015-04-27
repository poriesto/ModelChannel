cmake_minimum_required(VERSION 3.1)
set(PROJECT Diplom)
project(${PROJECT})
set(SOURCE_DIR src/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Wno-deprecated")

set(HEADERS_FILES
    ${SOURCE_DIR}api.hpp
    ${SOURCE_DIR}dsk.hpp)
set(SOURCE_FILES
    ${SOURCE_DIR}dsk.cpp)
	
add_executable(${PROJECT} ${HEADERS_FILES} ${SOURCE_FILES})
