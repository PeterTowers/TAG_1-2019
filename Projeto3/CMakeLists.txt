# cmake_minimum_required(VERSION <specify CMake version here>)
project(Projeto_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_3 src/graph.cpp src/reader.cpp src/matrix.cpp  src/Edge.cpp src/main.cpp include/Teacher.hpp include/School.hpp)