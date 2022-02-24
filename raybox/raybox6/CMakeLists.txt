cmake_minimum_required(VERSION 3.16)

project(raybox6)

file(GLOB CODIGO *.cpp)
# set(CODIGO main.cpp)

#include_directories("/usr/local/include")
include_directories("/usr/include/Box2D")

find_package(raylib 2.0 REQUIRED)
find_package(Box2D REQUIRED)

foreach(archivo ${CODIGO})
  message(${archivo})
endforeach(archivo)


add_executable(raybox6 ${CODIGO})

target_link_libraries(raybox6 raylib)
target_link_libraries(raybox6 Box2D)
