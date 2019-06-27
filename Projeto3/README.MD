# Project 3 - Stable sorting on a biparted weighed graph
This project constructs a weighted graph using '/data/materias.txt' file, utilizing adjacency list. We implemented the
following features to the graph:
1. Topological sorting;
2. Critical path; and
3. Print the graph on a `.dot` file in order to create an image of it.

## Compiling
The code can be compiled using `make` - a makefile is available at the root directory. Alternatively, a CMakeLists.txt is available on the root folder, allowing the binary to be generated using CMake.
Finally, the project has been developed using CLion, which can also be used to open the project and setting it up.

## Running
If you chose to compile it using the provided makefile, a symbolic link `(runner)` should be created at the root directory. Executing `./runner` should be enough to run the binary (no flags required).
If you chose to compile it via CMake, a binary is available withing the `cmake-build-debug` directory, and if you used the IDE, you can run it normally by opening the project.

## Stable Pairing
Given a biparted doubly weighed graph, a stable sorting algorithm (such as implemented) will generate a set of edges such that no two nodes from different edges share on the graph an edge of greater weight than the ones chosen for each. 

## Printing the result
This program prints the output on the following format:
`Escola <school id>: Professores <comma-separated teacher ids...> `