cmake_minimum_required(VERSION 3.1)
set(PROJECT Diplom)
project(${PROJECT})
set(SOURCE_DIR src/)
set(BINARY_DIR "bin/")
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic -Wno-deprecated")
set(DCMAKE_CXX_FLAGS "-std=c++11 -pedantic -Wno-deprecated")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/WinBin64/lib")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/WinBin64/include/GL;C:/WinBin64/include")
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
    ${SOURCE_DIR}area.h
    ${SOURCE_DIR}axis.h
    ${SOURCE_DIR}curve.h
    ${SOURCE_DIR}grid.h
    ${SOURCE_DIR}line.h
    ${SOURCE_DIR}plot.h
    ${SOURCE_DIR}Graph.h)
set(GRAPH_SOURCES
    ${SOURCE_DIR}area.cpp
    ${SOURCE_DIR}axis.cpp
    ${SOURCE_DIR}curve.cpp
    ${SOURCE_DIR}grid.cpp
    ${SOURCE_DIR}line.cpp
    ${SOURCE_DIR}plot.cpp
    ${SOURCE_DIR}Graph.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

add_library(protocol STATIC ${HEADERS_FILES} ${SOURCE_FILES})
add_library(unitTests STATIC ${SOURCE_DIR}UnitTestsApi.h ${SOURCE_DIR}UnitTestsApi.cpp)
add_library(graph STATIC ${GRAPH_HEADERS} ${GRAPH_SOURCES})

add_executable(${PROJECT} src/main.h src/main.cpp)
add_executable(oppTest src/OppUnitTest.cpp)
add_executable(dskTest src/DskUnitTest.cpp)
add_executable(paTest src/PaUnitTest.cpp)

target_link_libraries(${PROJECT} protocol graph pthread sfml-window sfml-system sfml-graphics)
target_link_libraries(oppTest unitTests protocol graph pthread sfml-window sfml-system sfml-graphics)
target_link_libraries(dskTest unitTests protocol graph pthread sfml-window sfml-system sfml-graphics)
target_link_libraries(paTest unitTests protocol graph pthread sfml-window sfml-system sfml-graphics)
