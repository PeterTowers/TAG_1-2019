# cmake_minimum_required(VERSION <specify CMake version here>)
project(Projeto_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_2 src/course.cpp src/graph.cpp  src/main.cpp src/reader.cpp src/topoSorting.cpp include/topoSorting.hpp)