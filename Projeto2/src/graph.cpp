#include "../include/graph.hpp"
#include "../include/course.hpp"


// Connects two nodes, by id. Requires a function that determines the unique id of a given node
template <class T>
bool digraph<T>::connect(unsigned int id1, unsigned int id2, std::function<unsigned int(T)> get_id) {
    T *c1 = nullptr, *c2 = nullptr;     // Declares and initializes auxiliary variables to nullptr

    for(auto&& c : nodes){              // Search whole graph for received nodes
        if (get_id(*c) == id1) c1 = c;
        if (get_id(*c) == id2) c2 = c;
    }

    if (c1 == nullptr || c2 == nullptr) return false;   // If one of them doesn't exist, returns false

    edges.push_back({ c1, c2 });        // Sets edge between vertexes and end method returning true
    // edges.push_back(std::pair<course*, course*>(c1, c2));

    return true;
}

// Method push() adds a node to the graph
template <class T>
void digraph<T>::push(T* value) {
    nodes.push_back(value);
}

// Method print_adj() prints adjacency list
template <class T>
void digraph<T>::print_adj() {

    // Variable for file handling
    std::ofstream outputFile;   

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERRASED
    outputFile.open("../data/adjacency_list.dot", std::ios::trunc);

    // Prints an error if the file wasn't openned correctly and exits program with code '-3'
    if (!outputFile) {
        std::cout << "Error: Could not open file for adjacency list." << std::endl;
        exit(-3);
    }

    // Prints header as a comment
    outputFile << "/* ----- UnB's Computer Science course's digraph ----- */\n";

    // Print the type of graph (digraph) followed by a title (label) to be displayed within the image
    outputFile << "digraph {\n";
    outputFile << "\tlabel=\"Digraph of UnB's CS course\";\n";

    // Builds graph with left-to-right orientation
    outputFile << "\trankdir=LR;\n";

    // Prints each node's id in 'nodes'...
    for (auto& node : nodes){

        // ... with an indentation
        outputFile << '\t' << node->id;

        bool hasAdjacent = true;

        // Followed by its adjacent nodes if there are any
        for (int i = 0; i < edges.size(); i++)    

            if (edges[i].first->id == node->id) {
                // These symbols: ' -> {' should be printed only once and only if the node has adjacents
                if (hasAdjacent) {
                    outputFile << " -> { ";

                    // Sets variable to false so symbols won't be printed again
                    hasAdjacent = false;
                }

                // Prints adjacent nodes to file followed by a single space. The last one isn't a problem
                outputFile << edges[i].second->id << ' ';
            }

        /* If node has an adjacent, 'hasAdjacent' will be set to false, so we need the opposite value for this condition
            in order to print the weight of the edge into the file
          */
        if (!hasAdjacent)
            outputFile << "}[label=\"" << node->credits << "\",weight=\"" << node->credits << "\"];\n";
        // If node doesn't have an adjacent, all that's needed is a semicolon and a newline
        else
            outputFile << ";\n";
    }

    // Prints '}' signifying the graph's end
    outputFile << '}';

    // Closes the file
    outputFile.close(); 
}

// Method print_ordered() prints a topologically-ordered version of the graph
template <class T>
void digraph<T>::print_ordered(std::function<void(T)> print_node){

    // Instantiates a variable to receive the output of method ordered()
    auto ordered = this->ordered();

    // Variable for file handling
    std::ofstream outputFile;   

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERRASED
    outputFile.open("../data/topological_order.dot", std::ios::trunc);

    // Prints an error if the file wasn't openned correctly and exits program with code '-4'
    if (!outputFile) {
        std::cout << "Error: Could not open file for adjacency list." << std::endl;
        exit(-4);
    }

    // Prints header as a comment
    outputFile << "/* ----- UnB's Computer Science course's topologically ordered digraph ----- */\n";

    // Print the type of graph (digraph) followed by a title (label) to be displayed within the image
    outputFile << "digraph {\n";
    outputFile << "\tlabel=\"Topologically ordered digraph of UnB's CS course\";\n";
    outputFile << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    for (int i = 0; i < ordered.size(); i++){   // Iterates through vector ordered
        outputFile << '\t' << ordered[i]->id;   // Insert indentation

        int index = 0;  // Sets variable to find node's index inside 'nodes' vector

        while (ordered[i]->id != nodes[index]->id)
            index++;

        auto neighborhood = neighbors(index);   // Look for node's neighbors

        if (neighborhood.empty()) { // If node has no neighbors, print semicolon, newline and move to next node
            outputFile << ";\n";
            continue;
        }
        else {                      // If node has neighbors, prints them accordingly and current node's weight to edge
            outputFile << " -> { ";
            for (auto neighbor : neighborhood) {
                outputFile << nodes[neighbor]->id << ' ';
            }
            outputFile << "}[label=\"" << nodes[index]->credits << "\",weight=\"" << nodes[index]->credits << "\"];\n";
        }
    }

    // Prints '}' signifying the graph's end
    outputFile << '}';

    outputFile.close(); // Closes the file
}

// Method neighbors() receives a vertex's id and returns the positions of its edges on the edges array
template <class T>
std::vector<unsigned int> digraph<T>::neighbors(unsigned int index) {
    // Variable that will receive
    std::vector<unsigned int> output;

    for(int i = 0; i < edges.size(); i++)   // Iterates through each edge
        if(edges[i].first == nodes[index])  // If the edge's source is the requested node
            output.push_back(i);            // Save that edge

    // Returns the saved edges
    return output;
}

// Recursive method orderred() implements digraph's topological sort
template <class T>
std::vector<T*> digraph<T>::ordered(std::vector<bool> visited, std::vector<T*> output) {
  
  // Initializes visited array on the method call
  if (visited.empty())
    for(auto node : nodes)
      visited.push_back(false);

  // Implements a DFS on digraph in order to...
  for (int i = 0; i < nodes.size(); i++){
    // if(output.count() == nodes.count()) break; // All nodes have been visited

    visited[i] = true;      // Mark the current node temporarily
    auto node = nodes[i];   // Stores i-th node inside 'node' variable
    output.push_back(node); // Push current node into the output stack, permanently marking it

    // Ignore node if it has been permanently visited
    if(std::find(output.begin(), output.end(), node) != output.end()) continue;

    // Visit node's adjacent nodes
    for(auto neighbor : neighbors(i)) {

      // Cycle Detection: If digraph has a cycle, prints an error and exit with condition "-1"
      if(visited[neighbor]) {
        std::cout << "[digraph::ordered] error: found cycle (" << i << ',' << neighbor << ')' << std::endl;
        exit(-1);
      }

      /** Recursion
       *   Pushes entire topologically ordered subgraph starging from
       *    current neighbor into the stack first, recursively.
       */
      if(std::find(output.begin(), output.end(), node) == output.end())
        for(auto stacked : ordered(visited, output))
          output.push_back(stacked);
    }
  }

  // Returns a topologically ordered list of nodes
  return output;
}

template <class T>
std::vector<T*> digraph<T>::critical_path(std::vector<bool> visited, std::vector<T*> output) {

}
 template class digraph<course>;