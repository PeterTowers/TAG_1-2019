# cmake_minimum_required(VERSION <specify CMake version here>)
project(Projeto_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_3 src/Graph.cpp src/reader.cpp src/Matrix.cpp  src/Edge.cpp src/main.cpp include/Teacher.hpp include/School.hpp)