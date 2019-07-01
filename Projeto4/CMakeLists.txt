# cmake_minimum_required(VERSION <specify CMake version here>)
project(Projeto_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto_4 include/Sudoku.hpp src/main.cpp src/Sudoku.cpp src/Cell.cpp include/Cell.hpp include/UserInterface.hpp src/UserInterface.cpp)