#include "../include/printer.hpp"

// print_to_console prints the content of a vector of Edges to the console
void print_to_console(std::vector<Edge> edges) {
    // Prints a header before the result
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Impressao do pareamento:\nUma escola ou vaga associada ao elemento 'P0' indica ";
    std::cout << "que ela nao foi pareada a\nnenhum professor." << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n" << std::endl;

    int i = 0;  // Auxiliary variable to count printed edges

    // Iterates through vector of edges
    for (auto& edge : edges) {
        std::cout << "Escola: E" << edge.from() << " -> ";  // School related
        std::cout << "Professor: P" << edge.to();           // Teacher related

        i++;    // Counts printed edges

        // End line every 2 pair of edges printed or insert a horizontal tab
        if ( (i%2) == 0 )
            std::cout << std::endl;
        else
            std::cout << " \t";
    }
}