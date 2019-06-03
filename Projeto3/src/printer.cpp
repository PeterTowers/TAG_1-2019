#include "../include/printer.hpp"

// print_to_console prints the content of a vector of Edges to the console
void print_to_console(std::vector<Edge> edges) {
    // Prints a header before the result
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Impressao do pareamento:\nUma escola ou vaga associada ao elemento 'P0' indica ";
    std::cout << "que ela nao foi pareada a\nnenhum professor." << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n" << std::endl;

    int i = 0;  // Auxiliary variable to count printed edges
    int last_school = -1;

    // Iterates through vector of edges
    for (auto& edge : edges) {
        // std::cout << "from: " << edge.from() << " | last: " << last_school; 

        if ((int) edge.from() > last_school){
          last_school = edge.from();
          std::cout << std::endl
                    << "Escola: E"
                    << edge.from() << " -> " // School related
                    << "Professores: ";
        }
        else std::cout << ", ";
        std::cout << "P" << edge.to();           // Teacher related

        i++;    // Counts printed edges

        // // End line every 2 pair of edges printed or insert a horizontal tab
        // if ( (i%2) == 0 )
        //     std::cout << std::endl;
        // else
        //     std::cout << " \t";
    }
}

// Function print_adj() prints adjacency list
template<class T>
void print_adj(std::vector<School> schools, std::vector<Teacher> teachers) {

    // Variable for file handling
    std::ofstream outputFile;

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERASED
    outputFile.open("../data/adjacency_list.dot", std::ios::trunc);

    // Prints an error if the file wasn't opened correctly and exits program with code '-3'
    if (!outputFile) {
        std::cout << "Error: Could not open file for adjacency list." << std::endl;
        exit(-3);
    }

    auto find_element_by_id = [](std::vector<Node> elements, int id) {
        for (int i = 0; i < elements.size(); i++)
            if (elements[i].get_id() == id)
                return i;

        return -1;
    };

    // Prints header as a comment
    outputFile << "/* ----- Grafo relacionando professores e escolas desejadas ----- */\n";

    // Print the type of graph (graph) followed by a title (label) to be displayed within the image
    outputFile << "graph {\n";
    outputFile << "\tlabel=\"Grafo relacionando professores e escolas desejadas\";\n";

    // Builds graph with left-to-right orientation (no need for this here)
    //outputFile << "\trankdir=LR;\n";

    // Prints each node's id in 'nodes'...
    for (auto& teacher : teachers) {
        for (int i = 0; i < teacher.get_schools().size(); i++) {
            // ... with an indentation
            outputFile << "\tP" << teacher.get_id() << " -- E";

            int schoolIndex = find_element_by_id(schools, teacher.get_schools()[i]);

            if (schoolIndex != -1) {
                outputFile << schools[schoolIndex];
                outputFile << "[label=\"" << i+1 << "\",weight=\"" << i+1 << "\"];\n";
            }

            else {
                std::cout << "Error: could not find school id." << std::endl;
                exit(-4);
            }
        }

    }

    // Prints '}' signifying the graph's end
    outputFile << '}';

    // Closes the file
    outputFile.close();
}