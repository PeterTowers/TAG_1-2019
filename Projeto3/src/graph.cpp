#include <algorithm>
#include "../include/graph.hpp"
#include "../include/course.hpp" // FIXME: This is an antipattern

template <class T>
bool graph<T>::connected(unsigned int target, unsigned int source){
  bool are = false;

  // Iterate over edges
  for (auto &&edge : edges)
    if (edge.from(source) && edge.to(target) //  Check if the edge matches requested nodes
    || (directed ? false : edge.involves(source) && edge.involves(target))) // Check it reversed if the graph is not directed
      are = true;
  
  return are;
}

// Connects two nodes, by id.
template <class T>
bool graph<T>::connect(unsigned int id1, unsigned int id2, int weight) {
    int source = find_node_by_id(id1);
    int target = find_node_by_id(id2);

    if (source < 0 || target < 0) return false; // If one of them doesn't exist, returns false

    edges.emplace_back((unsigned int) source, (unsigned int) target, weight); // Sets edge between vertexes and end method returning true

    return true;
}

// Method find_node_by_id() returns a node's index on 'nodes' vector by searching for its id
template <class T>
int graph<T>::find_node_by_id(unsigned int id) {
    

    for (int i = 0; i < nodes.size(); i++)
      if (nodes[i].id == id) return i;

    return -1;
}

// Method print_adj() prints adjacency list
template <class T>
void graph<T>::inspect(std::function<void(Node)> print, std::string separator) {
    for (int i = 0; i < nodes.size(); i++){
      auto& node = nodes[i];
      bool first = true;

      print(node);

      std::cout << " -> { ";

      for (auto& neighbor : neighbors(i)){
        if (!first) std::cout << separator;
        print(nodes[neighbor]);
        first = false;
      }

      std::cout << " } " << std::endl;
    }
}


// Method find_critical_path() returns the index of the critical path on 'criticalPaths' vector
template <class T>
unsigned int graph<T>::find_critical_path(std::vector<std::pair<std::vector<unsigned int>, int>> criticalPaths) {
    // int maxWeight = 0;              // Auxiliary variable to store a path's sum of weights
    // std::vector<unsigned int> path; // path stores indices of critical paths with the same sum of weights

    // // Iterates through vector to find path with biggest weight.
    // for (int i = 0; i < criticalPaths.size(); i++)
    //     if (criticalPaths[i].second > maxWeight)
    //         maxWeight = criticalPaths[i].second;

    // // Iterates through vector again to find if there are other paths with the same weight
    // for (int i = 0; i < criticalPaths.size(); i++)
    //     if (criticalPaths[i].second == maxWeight)
    //         path.push_back(i);  // Saves paths with the biggest weight

    // // If there's more than one path with the same maximal weight, looks for the one with the most nodes
    // if (path.size() > 1) {
    //     unsigned  int index = path[0];

    //     for (int i = 0; i < (path.size() - 1); i++) {
    //         if (criticalPaths[path[i]].first.size() < criticalPaths[path[i+1]].first.size())
    //             index = path[i+1];
    //     }

    //     return index;   // Returns the index of the path with the most nodes
    // }

    // else
    //     return path[0]; // Returns the index of the path with the biggest weight

    return 0;
}

// Method push() adds a node to the graph. IMPORTANT: If an ID is not provided, it will default to using the actual array index.
template <class T>
void graph<T>::push(T* value, int id) {
    nodes.emplace_back(value, (id < 0) ? nodes.size() : id);
}

// Method print_adj() prints adjacency list
template <class T>
void graph<T>::print_adj() {

    // Variable for file handling
    std::ofstream outputFile;

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERASED
    outputFile.open("../data/adjacency_list.dot", std::ios::trunc);

    // Prints an error if the file wasn't opened correctly and exits program with code '-3'
    if (!outputFile) {
        std::cout << "Error: Could not open file for adjacency list." << std::endl;
        exit(-3);
    }

    // // Prints header as a comment
    // outputFile << "/* ----- UnB's Computer Science course's graph ----- */\n";

    // // Print the type of graph (graph) followed by a title (label) to be displayed within the image
    // outputFile << "graph {\n";
    // outputFile << "\tlabel=\"graph of UnB's CS bachelor courses\";\n";

    // // Builds graph with left-to-right orientation
    // outputFile << "\trankdir=LR;\n";

    // // Prints each node's id in 'nodes'...
    // for (auto& node : nodes) {
    //     // ... with an indentation
    //     outputFile << '\t' << node->id;

    //     bool hasAdjacent = true;

    //     // Followed by its adjacent nodes if there are any
    //     for (int i = 0; i < edges.size(); i++)
    //         if (edges[i].source->id == node->id) {
    //             // These symbols: ' -> {' should be printed only once and only if the node has adjacents
    //             if (hasAdjacent) {
    //                 outputFile << " -> { ";

    //                 // Sets variable to false so symbols won't be printed again
    //                 hasAdjacent = false;
    //             }
    //             // Prints adjacent nodes to file followed by a single space. The last one isn't a problem
    //             outputFile << edges[i].second->id << ' ';
    //         }

    //     /* If node has an adjacent, 'hasAdjacent' will be set to false, so we need the opposite value for this condition
    //         in order to print the weight of the edge into the file
    //       */
    //     if (!hasAdjacent)
    //         outputFile << "}[label=\"" << node->credits << "\",weight=\"" << node->credits << "\"];\n";
    //     // If node doesn't have an adjacent, all that's needed is a semicolon and a newline
    //     else
    //         outputFile << ";\n";
    // }

    // // Prints '}' signifying the graph's end
    // outputFile << '}';

    // Closes the file
    outputFile.close();
}

// Method print_ordered() prints a topologically-ordered version of the graph
template <class T>
void graph<T>::print_ordered(std::function<void(T)> print_node) {
    // Instantiates a variable to receive the output of method ordered()
    auto ordered = this->ordered();

    // Variable for file handling
    std::ofstream outputFile;

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERASED
    outputFile.open("../data/topological_order.dot", std::ios::trunc);

    // // Prints an error if the file wasn't opened correctly and exits program with code '-4'
    // if (!outputFile) {
    //     std::cout << "Error: Could not open file for adjacency list." << std::endl;
    //     exit(-4);
    // }

    // // Prints header as a comment
    // outputFile << "/* ----- UnB's Computer Science course's topologically ordered graph ----- */\n";

    // // Print the type of graph (graph) followed by a title (label) to be displayed within the image
    // outputFile << "graph {\n";
    // outputFile << "\tlabel=\"Topologically ordered graph of UnB's CS bachelor courses\";\n";
    // outputFile << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    // for (int i = 0; i < ordered.size(); i++){   // Iterates through vector ordered
    //     outputFile << '\t' << ordered[i]->id;   // Insert indentation

    //     int index = find_node_by_id(ordered[i]->id);  // Look for node's index inside 'nodes' vector

    //     auto neighborhood = neighbors(index);   // Look for node's neighbors

    //     if (neighborhood.empty()) { // If node has no neighbors, print semicolon, newline and move to next node
    //         outputFile << ";\n";
    //         continue;
    //     }
    //     else {                      // If node has neighbors, prints them accordingly and current node's weight to edge
    //         outputFile << " -> { ";
    //         for (auto edge : neighborhood) {
    //             unsigned int neighbor = edges[edge].second->id;
    //             neighbor = find_node_by_id(neighbor);

    //             outputFile << nodes[neighbor]->id << ' ';
    //         }
    //         outputFile << "}[label=\"" << nodes[index]->credits << "\",weight=\"" << nodes[index]->credits << "\"];\n";
    //     }
    // }

    // // Prints '}' signifying the graph's end
    // outputFile << '}';

    outputFile.close(); // Closes the file
}

// Method critical_path() finds the graph's critical path and prints it to file
template <class T>
void graph<T>::critical_path() {
    // // Checks if graph has edges. If it doesn't, exits with code '-2'.
    // if (edges.empty()) {
    //     std::cout << "Error: graph has no edges." << std::endl;
    //     exit(-2);
    // }

    // // Sets up and initializes an array to represent visited nodes
    // std::vector<bool> visited;
    // for(auto node : nodes)
    //     visited.push_back(false);

    // /*
    //   Define a container for the graph's critical paths and size it according to nodes, since each node will have its
    //    critical path.
    //  */
    // std::vector<std::pair<std::vector<unsigned int>, int>> graphCriticalPaths = { { } };
    // graphCriticalPaths.resize(nodes.size());

    // // Iterates through graph
    // for (int i = 0; i < nodes.size(); i++) {
    //     // If a node has been visited before, it already has a critical path, so, moves on
    //     if (visited[i])
    //         continue;

    //     // Calls path_finder() on node to find its critical path
    //     graphCriticalPaths = path_finder(graphCriticalPaths, visited, i);
    // }

    // // Calls find_critical_path() to find the index of the critical path on 'graphCriticalPaths' vector
    // unsigned int index = find_critical_path(graphCriticalPaths);

    // // Saves the critical
    // std::pair<std::vector<unsigned int>, int> theCriticalPath = graphCriticalPaths[index];

    // // Calls print_critical_path() to print subgraph to file
    // print_critical_path(theCriticalPath.first);
}

template <class T>
void graph<T>::print_critical_path(std::vector<unsigned int> criticalPath) {
    // /* Sets a variable for file handling and opens file in WRITE mode, passing 'trunc' parameter so that if there's a
    //    previous file, it'll be ERRASED
    //  */
    // std::ofstream print_crit("../data/critical_path.dot", std::ios::trunc);

    // // Prints an error if the file wasn't opened correctly and exits program with code '-5'
    // if (!print_crit) {
    //     std::cout << "Error: could not open file for critical path." << std::endl;
    //     exit(-5);
    // }

    // // Prints header as a comment
    // print_crit << "/* ----- UnB's Computer Science course's critical path subgraph ----- */\n";

    // // Print the type of graph (graph) followed by a title (label) to be displayed within the image
    // print_crit << "graph {\n";
    // print_crit << "\tlabel=\"Subgraph containing the critical path of UnB's CS bachelor courses\";\n";
    // print_crit << "\trankdir=LR;\n";    // Builds graph with left-to-right orientation

    // // Prints node's id, followed by its adjacent's id, with its weight (credits) information
    // for (int i = 0; i < (criticalPath.size() - 1); i++){
    //     print_crit << '\t' << nodes[criticalPath[i]]->id << " -> " << nodes[criticalPath[i+1]]->id;
    //     print_crit << "[label=\"" << nodes[i]->credits << "\",weight=\"" << nodes[i]->credits << "\"];\n";
    // }

    // // Prints '}' signifying the graph's end
    // print_crit << '}';

    // print_crit.close(); // Closes the file

}

// Method neighbors() receives a vertex's id and returns the positions of its neighbors on the nodes array
template <class T>
std::vector<unsigned int> graph<T>::neighbors(unsigned int index) {
    // Variable that will receive
    std::vector<unsigned int> output;


    // Edges which depart from current node
    for(auto edge : edges) // Iterates through each edge
        if(edge.from(index))      // If the edge's source is the requested node
            output.push_back(edge.to());          // Save that edge
            

    // Edges which terminate at current node, if the graph is not directed
    if (!directed)
      for(auto edge : edges) // Iterates through each edge
        if(edge.to(index))      // If the edge's target is the requested node
          output.push_back(edge.from());


    output.erase(std::unique(output.begin(), output.end()), output.end());

    // Returns the saved edges
    return output;
}

// Recursive method orderred() implements graph's topological sort
template <class T>
std::vector<T*> graph<T>::ordered(std::vector<bool> visited, std::vector<T*> output) {
  // // Initializes visited array on the method call
  // if (visited.empty())
  //   for(auto node : nodes)
  //     visited.push_back(false);

  // // Implements a DFS on graph in order to...
  // for (int i = 0; i < nodes.size(); i++){
  //   // if(output.count() == nodes.count()) break; // All nodes have been visited

  //   visited[i] = true;      // Mark the current node temporarily
  //   auto node = nodes[i];   // Stores i-th node inside 'node' variable
  //   output.push_back(node); // Push current node into the output stack, permanently marking it

  //   // Ignore node if it has been permanently visited
  //   if(std::find(output.begin(), output.end(), node) != output.end()) continue;

  //   // Visit node's adjacent nodes
  //   for(auto neighbor : neighbors(i)) {
  //     // Cycle Detection: If graph has a cycle, prints an error and exit with condition "-1"
  //     if(visited[neighbor]) {
  //       std::cout << "[graph::ordered] error: found cycle (" << i << ',' << neighbor << ')' << std::endl;
  //       exit(-1);
  //     }

  //     /** Recursion
  //      *   Pushes entire topologically ordered subgraph starging from
  //      *    current neighbor into the stack first, recursively.
  //      */
  //     if(std::find(output.begin(), output.end(), node) == output.end())
  //       for(auto stacked : ordered(visited, output))
  //         output.push_back(stacked);
  //   }
  // }

  // // Returns a topologically ordered list of nodes
  return output;
}

// Method path_finder() calculates a critical path for every node
template <class T>
std::vector<std::pair<std::vector<unsigned int>, int>> graph<T>::path_finder(
        std::vector<std::pair<std::vector<unsigned int>, int>> criticalPath, std::vector<bool> visited,
        unsigned int index) {
    // Checks if node has been visited before, if so, its critical path is already calculated
    if (visited[index])
        return criticalPath;

    // // Otherwise, set node as visited
    // visited[index] = true;

    // // Find node's adjacent veterxes
    // std::vector<unsigned int> neighborhood = neighbors(index);

    // // If node has no neighbors, then its critical path is set as itself, with its own weight (credits)
    // if (neighborhood.empty()) {
    //     criticalPath[index].first.push_back(index);
    //     criticalPath[index].second = nodes[index]->credits;
    //     return criticalPath;
    // }

    // // Setting auxiliary variables to track max calculated weight, current calculated weight and current path
    // int maxWeight, auxWeight;
    // maxWeight = auxWeight = 0;
    // std::vector<unsigned int> maxPath;

    // // Iterates through node's neighbors
    // for (auto edge : neighborhood) {
    //     // Finds adjacent nodes' id from 'edges' vector and finds node's position in 'nodes' vector
    //     unsigned int neighbor = edges[edge].second->id;
    //     neighbor = find_node_by_id(neighbor);

    //     // Recursively call method onto neighbors passing updated values
    //     criticalPath = path_finder(criticalPath, visited, neighbor);

    //     auxWeight += criticalPath[neighbor].second; // Sets current weight to self plus that of a given path

    //     // If current calculated weight is greater than max, we have a new critical path
    //     if (auxWeight > maxWeight) {
    //         maxWeight = auxWeight;  // Set new maximal weight
    //         maxPath = criticalPath[neighbor].first; // Save path in auxiliary variable
    //     }
    //     // Resets auxWeight to default value for next comparisons
    //     auxWeight = 0;
    // }

    // // After checking all neighbors, we'll have a critical path for the node
    // criticalPath[index].first = maxPath;                                        // Saves path for current node
    // criticalPath[index].first.insert(criticalPath[index].first.begin(), index); // Insert current node into path

    // // Save this node's critical path weight as the sum of the path's weights
    // criticalPath[index].second = maxWeight + nodes[index]->credits;

    return criticalPath;    // Returns vector containing calculated critical path
}

template class graph<course>; // FIXME: This is an antipattern