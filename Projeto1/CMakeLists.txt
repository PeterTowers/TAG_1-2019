cmake_minimum_required(VERSION 3.13)
project(projeto1 C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto1 main.c readgml.c program.c bronkerbosch.c bklist.c agglomeration.c)