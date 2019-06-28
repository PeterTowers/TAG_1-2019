# cmake_minimum_required(VERSION <specify CMake version here>)
project(Projeto_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_4 include/sudoku.hpp src/main.cpp src/sudoku.cpp src/Cell.cpp include/Cell.hpp)