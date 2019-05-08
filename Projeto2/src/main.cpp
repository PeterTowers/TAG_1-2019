#include <iostream>
#include "../include/reader.hpp"
#include "../include/graph.hpp"
#include "../include/topoSorting.hpp"

int main(int argc, char const *argv[])
{

    // std::vector<std::string> args;

    // for(int i = 1; i < argc; i++) // skip program name
    //     args.push_back(argv[i]);


    // // Supondo filename como arg[0]
    // auto graph = read(args[0]);
    // if (graph == nullptr) return -1;

    digraph<course>* graph = build("../data/materias.txt");
    graph->print_adj();

    int i = topo_sorting(graph);

    return i;
}
