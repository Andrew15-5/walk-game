cmake_minimum_required(VERSION 2.8.12)

project(walk-game)

include_directories(${CMAKE_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(binary_name ${PROJECT_NAME})
set(compile_flags -g -Og -Wall -Werror)
set(libraries GL glut)

add_subdirectory(src)
