#include <algorithm>
#include "../include/Graph.hpp"

bool Graph::connected(unsigned int target, unsigned int source){
  bool are = false;

  // Iterate over edges
  for (auto &&edge : edges)
    if (edge.from(source) && edge.to(target) //  Check if the edge matches requested nodes
    || (directed ? false : edge.involves(source) && edge.involves(target))) // Check it reversed if the graph is not directed
      are = true;
  
  return are;
}

// Connects two nodes, by id.
bool Graph::connect(unsigned int id1, unsigned int id2, int weight) {
    int source = find_node_by_id(id1);
    int target = find_node_by_id(id2);

    if (source < 0 || target < 0) return false; // If one of them doesn't exist, returns false

    edges.emplace_back((unsigned int) source, (unsigned int) target, weight); // Sets edge between vertexes and end method returning true

    return true;
}

// Method find_node_by_id() returns a node's index on 'nodes' vector by searching for its id
int Graph::find_node_by_id(unsigned int id) {
    for (int i = 0; i < nodes.size(); i++)
      if (nodes[i].get_id() == id) return i;

    return -1;
}

// Method print_adj() prints adjacency list
void Graph::inspect(std::function<void(Node)> print, std::string separator) {
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
unsigned int Graph::find_critical_path(std::vector<std::pair<std::vector<unsigned int>, int>> criticalPaths) {
  // Deprecated method
  return 0;
}

// Method push() adds a node to the graph. IMPORTANT: If an ID is not provided, it will default to using the actual array index.
void Graph::push(Node& value) {
    nodes.push_back(value);
}

// Method print_adj() prints adjacency list
void Graph::print_adj() {

    // Variable for file handling
    std::ofstream outputFile;

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERASED
    outputFile.open("../data/adjacency_list.dot", std::ios::trunc);

    // Prints an error if the file wasn't opened correctly and exits program with code '-3'
    if (!outputFile) {
        std::cout << "Error: Could not open file for adjacency list." << std::endl;
        exit(-3);
    }

    // Closes the file
    outputFile.close();
}

// Method print_ordered() prints a topologically-ordered version of the graph
void Graph::print_ordered(std::function<void(Node)> print_node) {
    // Instantiates a variable to receive the output of method ordered()
    auto ordered = this->ordered();

    // Variable for file handling
    std::ofstream outputFile;

    // Open file in WRITE mode, passing 'trunc' parameter so that if there's a previous file, it'll be ERASED
    outputFile.open("../data/topological_order.dot", std::ios::trunc);

    outputFile.close(); // Closes the file
}

// Method critical_path() finds the graph's critical path and prints it to file
void Graph::critical_path() {
  // Deprecated method
}

void Graph::print_critical_path(std::vector<unsigned int> criticalPath) {
  // Deprecated method
}

// Method neighbors() receives a vertex's id and returns the positions of its neighbors on the nodes array
std::vector<unsigned int> Graph::neighbors(unsigned int index) {
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


// Deprecated method 
std::vector<Node> Graph::ordered(std::vector<bool> visited, std::vector<Node> output) {
  // Deprecated method
  return output;
}


// Deprecated method 
std::vector<std::pair<std::vector<unsigned int>, int>> Graph::path_finder(
        std::vector<std::pair<std::vector<unsigned int>, int>> criticalPath, std::vector<bool> visited,
        unsigned int index) {
    // Deprecated method
    if (visited[index])
        return criticalPath;

    return criticalPath;    // Returns vector containing calculated critical path
}