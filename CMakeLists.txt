cmake_minimum_required(VERSION 3.16)

project(dulcemetal)

file(GLOB CODIGO *.cpp)
# set(CODIGO main.cpp)

#include_directories("/usr/local/include")
include_directories("/usr/include/Box2D")

find_package(raylib 2.0 REQUIRED)
find_package(Box2D REQUIRED)

add_executable(dulcemetal ${CODIGO})

target_link_libraries(dulcemetal raylib)
target_link_libraries(dulcemetal Box2D)
