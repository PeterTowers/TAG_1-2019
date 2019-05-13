#include "../include/graph.hpp"
#include "../include/course.hpp"

// template <class T>
// std::vector<T*> digraph<T>::nodes() { return this.nodes };

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
// ----------------------------------- Prints to screen on terminal -----------------------------------
//    std::cout << "[print_adj] Printing adjacency list: " << std::endl;  // Prints a "header"
//
//    for (auto& node : nodes){       // Prints each node in 'nodes'
//        std::cout << "[print_adj] "
//                  << node->id
//                  << " -> ";
//
//        for (auto& edge : edges)    // Followed by its adjacent nodes
//            if (edge.first->id == node->id)
//                std::cout << edge.second->id << ' ';
//
//        std::cout << std::endl;
//    }
// ----------------------------------------------------------------------------------------------------
// --------------- Prints to 'adjacency_list.dot' file, located at '../data/' directory ---------------

    std::ofstream outputFile;   // Variable for file handling

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
    outputFile << "\tlabel=\"Digraph of UnB's CS bachelor courses\";\n";
    outputFile << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    for (auto& node : nodes){       // Prints each node's id in 'nodes'...
        outputFile << '\t' << node->id; // ... with an indentation

        bool hasAdjacent = true;

        for (int i = 0; i < edges.size(); i++)    // Followed by its adjacent nodes if there are any
            if (edges[i].first->id == node->id) {
                // These symbols: ' -> {' should be printed only once and only if the node has adjacents
                if (hasAdjacent) {
                    outputFile << " -> { ";
                    hasAdjacent = false;    // Sets variable to false so symbols won't be printed again
                }
                // Prints adjacent nodes to file followed by a single space. The last one isn't a problem
                outputFile << edges[i].second->id << ' ';
            }

        // If node has an adjacent, 'hasAdjacent' will be set to false, so we need the opposite value for this condition
        if (!hasAdjacent)   // in order to print the weight of the edge into the file
            outputFile << "}[label=\"" << node->credits << "\",weight=\"" << node->credits << "\"];\n";
        // If node doesn't have an adjacent, all that's needed is a semicolon and a newline
        else
            outputFile << ";\n";
    }

    // Prints '}' signifying the graph's end
    outputFile << '}';

    outputFile.close(); // Closes the file
}

// Method print_ordered() prints a topologically-ordered version of the graph
template <class T>
void digraph<T>::print_ordered(std::function<void(T)> print_node){
    auto ordered = this->ordered(); // Sets a variable to receive the output of method ordered()

// ----------------------------------- Prints to screen on terminal -----------------------------------
//    for (int i = 0; i < ordered.size(); i++){
//        std::cout << "node: ";
//        print_node(*nodes[i]);
//        std::cout << std::endl;
//    }
// ----------------------------------------------------------------------------------------------------
// -------------- Prints to 'topological_order.dot' file, located at '../data/' directory -------------

    std::ofstream outputFile;   // Variable for file handling

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
    outputFile << "\tlabel=\"Topologically ordered digraph of UnB's CS bachelor courses\";\n";
    outputFile << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    for (int i = 0; i < ordered.size(); i++){   // Iterates through vector ordered
        outputFile << '\t' << ordered[i]->id;   // Insert indentation

        int index = find_node_by_id(ordered[i]->id);  // Look for node's index inside 'nodes' vector

        auto neighborhood = neighbors(index);   // Look for node's neighbors

        if (neighborhood.empty()) { // If node has no neighbors, print semicolon, newline and move to next node
            outputFile << ";\n";
            continue;
        }
        else {                      // If node has neighbors, prints them accordingly and current node's weight to edge
            outputFile << " -> { ";
            for (auto edge : neighborhood) {
                unsigned int neighbor = edges[edge].second->id;
                neighbor = find_node_by_id(neighbor);

                outputFile << nodes[neighbor]->id << ' ';
            }
            outputFile << "}[label=\"" << nodes[index]->credits << "\",weight=\"" << nodes[index]->credits << "\"];\n";
        }
    }

    // Prints '}' signifying the graph's end
    outputFile << '}';

    outputFile.close(); // Closes the file
}

// Method neighbors() receives a vertex's index and returns its neighbors' indices
template <class T>
std::vector<unsigned int> digraph<T>::neighbors(unsigned int index) {
    std::vector<unsigned int> output;

    for(int i = 0; i < edges.size(); i++)
        if(edges[i].first == nodes[index])
            output.push_back(i);

        return output;
}

// Recursive method orderred() implements digraph's topological sort
template <class T>
std::vector<T*> digraph<T>::ordered(std::vector<bool> visited, std::vector<T*> output) {

  // Initializes visited array on the method call
  if (visited.empty())
    for(auto node : nodes)
      visited.push_back(false);

  // 1. Chamar dfsTodosVertices em G para computar f[v] para cada vértice v //TODO: explain this better
  // Implements a DFS on digraph in order to...
  for (int i = 0; i < nodes.size(); i++){
    // if(output.count() == nodes.count()) break; // All nodes have been visited

    visited[i] = true;      // Sets i-th node as visited
    auto node = nodes[i];   // Stores i-th node inside 'node' variable
    output.push_back(node); // Pushes 'node' inside 'output' vector

    // If node has been visited on current iteration, skips to the next one
    if(std::find(output.begin(), output.end(), node) != output.end()) continue;

    for(auto neighbor : neighbors(i)) { // Visit node's adjacent nodes

      // 2. Se G contém uma aresta retorno (v, w) (i.e., se f[w] > f[v]) , reportar erro ;
      // If digraph has a cycle, prints an error and exit with condition "-1"
      if(visited[neighbor]) {
        std::cout << "[digraph::ordered] error: found cycle (" << i << ',' << neighbor << ')' << std::endl;
        exit(-1);
      }

      // Stacks neighbors and move on to next one
      if(std::find(output.begin(), output.end(), node) == output.end())
        for(auto stacked : ordered(visited, output))
          output.push_back(stacked);
    }

  }

  return output;    // Returns a topologically ordered list of nodes
}

template <class T>
std::vector<std::pair<std::vector<unsigned int>, int>> digraph<T>::path_finder(
        std::vector<std::pair<std::vector<unsigned int>, int>> criticalPath, std::vector<bool> visited,
        unsigned int index) {
    // Checks if node has been visited before, if so, its critical path is already calculated
    if (visited[index])
        return criticalPath;

    // Otherwise, set node as visited
    visited[index] = true;

    // Find node's adjacent veterxes
    std::vector<unsigned int> neighborhood = neighbors(index);

    // If node has no neighbors, then its critical path is set as itself, with its own weight (credits)
    if (neighborhood.empty()) {
        criticalPath[index].first.push_back(index);
        criticalPath[index].second = nodes[index]->credits;
        return criticalPath;
    }

    // Setting auxiliary variables to track max calculated weight, current calculated weight and current path
    int maxWeight, auxWeight;
    maxWeight = auxWeight = 0;
    std::vector<unsigned int> maxPath;

    // Iterates through node's neighbors
    for (auto edge : neighborhood) {
        // Finds adjacent nodes' id from 'edges' vector and finds node's position in 'nodes' vector
        unsigned int neighbor = edges[edge].second->id;
        neighbor = find_node_by_id(neighbor);

        // Recursively call method onto neighbors passing updated values
        criticalPath = path_finder(criticalPath, visited, neighbor);

        auxWeight += criticalPath[neighbor].second; // Sets current weight to self plus that of a given path

        // If current calculated weight is greater than max, we have a new critical path
        if (auxWeight > maxWeight) {
            maxWeight = auxWeight;  // Set new maximal weight
            maxPath = criticalPath[neighbor].first; // Save path in auxiliary variable
        }
        auxWeight = 0;     // Resets auxWeight to default value for next comparisons
    }

    // After checking all neighbors, we'll have a critical path for the node
    criticalPath[index].first = maxPath;                                        // Saves path for current node
    criticalPath[index].first.insert(criticalPath[index].first.begin(), index); // Insert current node into path

    criticalPath[index].second = maxWeight + nodes[index]->credits; // Save this node's critical path weight as the sum of the path's weights

    return criticalPath;    // Returns vector containing calculated critical path
}

template <class T>
void digraph<T>::critical_path() {
    // Checks if graph has edges. pos == 0 means it'll check only on the first method call
    if (edges.empty()) {
        std::cout << "Error: graph has no edges." << std::endl;
        exit(-2); // TODO: quit method instead of ending the whole program?
    }

    std::vector<bool> visited;

    for(auto node : nodes)
        visited.push_back(false);

    int maxWeight = 0;

    std::vector<std::pair<std::vector<unsigned int>, int>> graphCriticalPaths = { { } };
    graphCriticalPaths.resize(nodes.size());

    for (int i = 0; i < nodes.size(); i++) {
        if (visited[i])
            continue;

        graphCriticalPaths = path_finder(graphCriticalPaths, visited, i);
    }

    unsigned int index = find_critical_path(graphCriticalPaths);

    std::pair<std::vector<unsigned int>, int> theCriticalPath = graphCriticalPaths[index];

    // printf() debugging

    std::cout << "Critical path is:" << std::endl;
    for (auto node : theCriticalPath.first) {
        std::cout << nodes[node]->id << " -> ";
    }
    std::cout << "\nSum of nodes weight: " << theCriticalPath.second << std::endl;

    print_critical_path(theCriticalPath.first);
}

template <class T>
unsigned int digraph<T>::find_node_by_id(unsigned int id) {
    int index = 0;

    while (nodes[index]->id != id)
        index++;

    return index;
}

template <class T>
unsigned int digraph<T>::find_critical_path(std::vector<std::pair<std::vector<unsigned int>, int>> criticalPaths) {
    int maxWeight = 0;
    std::vector<unsigned int> path;

    for (int i = 0; i < criticalPaths.size(); i++)
        if (criticalPaths[i].second >= maxWeight) {
            maxWeight = criticalPaths[i].second;
            path.push_back(i);
        }

    if (path.size() > 1) {
        unsigned  int index = path[0];

        for (int i = 0; i < (path.size() - 1); i++) {
            if (criticalPaths[path[i]].first.size() < criticalPaths[path[i+1]].first.size())
                index = path[i+1];
        }

        return index;
    }

    else
        return path[0];
}

template <class T>
void digraph<T>::print_critical_path(std::vector<unsigned int> criticalPath) {

    std::ofstream print_crit("../data/critical_path.dot", std::ios::trunc);
    if (!print_crit) {
        std::cout << "Error: could not open file for critical path." << std::endl;
        exit(-5);
    }

    // Prints header as a comment
    print_crit << "/* ----- UnB's Computer Science course's critical path subgraph ----- */\n";

    // Print the type of graph (digraph) followed by a title (label) to be displayed within the image
    print_crit << "digraph {\n";
    print_crit << "\tlabel=\"Subgraph containing the critical path of UnB's CS bachelor courses\";\n";
    print_crit << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    for (int i = 0; i < (criticalPath.size() - 1); i++){
        print_crit << '\t' << nodes[criticalPath[i]]->id << " -> " << nodes[criticalPath[i+1]]->id;
        print_crit << "[label=\"" << nodes[i]->credits << "\",weight=\"" << nodes[i]->credits << "\"];\n";
    }

    // Prints '}' signifying the graph's end
    print_crit << '}';

    print_crit.close(); // Closes the file

}

// TODO: Função de busca em profundidade num grafo

 template class digraph<course>;