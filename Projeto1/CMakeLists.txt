cmake_minimum_required(VERSION 3.13)
project(proj1 C)

set(CMAKE_C_STANDARD 99)

add_executable(proj1 main.c readgml.c program.c)
include_directories(/home/pedro/Documents/TeoAppGrafos/proj1/)