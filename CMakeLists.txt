cmake_minimum_required(VERSION 3.1)
set(PROJECT Diplom)
project(${PROJECT})
set(SOURCE_DIR src/)
set(BINARY_DIR "bin/")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -Wno-deprecated")
set(DCMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -Wno-deprecated")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/MinGW/lib")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/MinGW/include/GL;C:/MinGW/include")

##########################################################
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(SEND_ERROR "Failed to find OpenGL")
    return()
else()
    include_directories(${OPENGL_INCLUDE_DIR})
endif()
##########################################################
find_package(GLUT REQUIRED)
if(NOT GLUT_FOUND)
    message(SEND_ERROR "Failed to find GLUT")
    return()
else()
    include_directories(${GLUT_INCLUDE_DIR})
endif()
##########################################################

#####################################################################
#SOURCE_FILES
######################################################################
set(HEADERS_FILES
    ${SOURCE_DIR}api.hpp
    ${SOURCE_DIR}dsk.hpp
    ${SOURCE_DIR}opp.h
    ${SOURCE_DIR}pa.h
    ${SOURCE_DIR}protocol.h)
set(SOURCE_FILES
    ${SOURCE_DIR}api.cpp
    ${SOURCE_DIR}opp.cpp
    ${SOURCE_DIR}dsk.cpp
    ${SOURCE_DIR}pa.cpp
    ${SOURCE_DIR}protocol.cpp)
set(GRAPH_HEADERS
    ${SOURCE_DIR}GLWindow.hpp
    ${SOURCE_DIR}Graph.h)
set(GRAPH_SOURCES
    ${SOURCE_DIR}GLWindow.cpp
    ${SOURCE_DIR}Graph.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

add_library(protocol STATIC ${HEADERS_FILES} ${SOURCE_FILES})
add_library(unitTests STATIC ${SOURCE_DIR}UnitTestsApi.h ${SOURCE_DIR}UnitTestsApi.cpp)
add_library(graph STATIC ${GRAPH_HEADERS} ${GRAPH_SOURCES})

add_executable(${PROJECT} src/main.h src/main.cpp)
add_executable(oppTest src/OppUnitTest.cpp)
add_executable(dskTest src/DskUnitTest.cpp)

target_link_libraries(${PROJECT} protocol ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(oppTest unitTests protocol graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(dskTest unitTests protocol graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
