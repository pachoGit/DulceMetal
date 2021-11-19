cmake_minimum_required(VERSION 3.16)

project(dulcemetal)

file(GLOB CODIGO *.cpp)
# set(CODIGO main.cpp)

#include_directories("/usr/local/include")

find_package(raylib 2.0 REQUIRED)

add_executable(dulcemetal ${CODIGO})

target_link_libraries(dulcemetal raylib)
