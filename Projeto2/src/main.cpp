#include <iostream>
#include "../include/reader.hpp"

int main(int argc, char const *argv[])
{

    std::vector<std::string> args;

    for(int i = 1; i < argc; i++) // skip program name
        args.push_back(argv[i]);


    // Supondo filename como arg[0]
    auto graph = read(args[0]);
    if (graph == nullptr) return -1;


    return 0;
}
