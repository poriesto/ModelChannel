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
    ${SOURCE_DIR}protocol.h
    ${SOURCE_DIR}GLWindow.hpp
    ${SOURCE_DIR}Graph.h
    ${SOURCE_DIR}UnitTestsApi.h
    ${SOURCE_DIR}main.h)
set(SOURCE_FILES
    ${SOURCE_DIR}api.cpp
    ${SOURCE_DIR}opp.cpp
    ${SOURCE_DIR}dsk.cpp
    ${SOURCE_DIR}pa.cpp
    ${SOURCE_DIR}protocol.cpp
    ${SOURCE_DIR}GLWindow.cpp
    ${SOURCE_DIR}UnitTestsApi.cpp
    ${SOURCE_DIR}Graph.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

add_executable(${PROJECT} ${HEADERS_FILES} src/main.h ${SOURCE_FILES} src/main.cpp)
add_executable(oppTest ${HEADERS_FILES} ${SOURCE_FILES} src/OppUnitTest.cpp)
add_executable(dskTest ${HEADERS_FILES} ${SOURCE_FILES} src/DskUnitTest.cpp)

target_link_libraries(${PROJECT} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(oppTest ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(dskTest ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

#target_link_libraries(oppTest
#                                  opengl32
#                                  glu32
#                                  freeglut)
#target_link_libraries(dskTest
#                                  GL
#                                  GLU
#                                  glut)
#target_link_libraries(${PROJECT}
#                                  GL
#                                 GLU
#                                  glut)
#target_link_libraries(oppTest
#                                  GL
#                                  GLU
#                                  glut)
#target_link_libraries(dskTest
#                                  GL
#                                  GLU
#                                  glut)
