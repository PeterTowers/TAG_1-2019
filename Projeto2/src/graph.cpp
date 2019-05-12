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
    std::cout << "[print_adj] Printing adjacency list: " << std::endl;  // Prints a "header"

    for (auto& node : nodes){       // Prints each node in 'nodes'
        std::cout << "[print_adj] "
                  << node->id
                  << " -> ";

        for (auto& edge : edges)    // Followed by its adjacent nodes
            if (edge.first->id == node->id)
                std::cout << edge.second->id << ' ';

        std::cout << std::endl;
    }
}

// Method print_ordered() prints a topologically-ordered version of the graph
template <class T>
void digraph<T>::print_ordered(std::function<void(T)> print_node){
    auto ordered = this->ordered();

    for (int i = 0; i < ordered.size(); i++){
        std::cout << "node: ";
        print_node(*nodes[i]);
        std::cout << std::endl;
    }
}

// Method neighbors() receives a vertex's index and returns its neighbors' indices
template <class T>
std::vector<unsigned int> digraph<T>::neighbors(unsigned int i) {
    std::vector<unsigned int> output;

    for(int i = 0; i < edges.size(); i++)
        if(edges[i].first == nodes[i])
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
        unsigned int index, int weight) {
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

    // Sets default weight value to current iteration
    weight += nodes[index]->credits;

    // Setting auxiliary variables to track max calculated weight, current calculated weight and current path
    int maxWeight, auxWeight;
    maxWeight = auxWeight = weight;
    std::vector<unsigned int> maxPath;

    // Iterates through node's neighbors
    for (auto neighbor : neighborhood) {
        // Recursively call method onto neighbors passing updated values
        criticalPath = path_finder(criticalPath, visited, neighbor, weight);

        auxWeight += criticalPath[neighbor].second; // Sets current weight to self plus that of a given path

        // If current calculated weight is greater than max, we have a new critical path
        if (auxWeight > maxWeight) {
            maxWeight = auxWeight;  // Set new maximal weight
            auxWeight = weight;     // Resets auxWeight to default value for next comparisons

            maxPath = criticalPath[neighbor].first; // Save path in auxiliary variable
        }
    }

    // After checking all neighbors, we'll have a critical path for the node
    criticalPath[index].first = maxPath;                                        // Saves path for current node
    criticalPath[index].first.insert(criticalPath[index].first.begin(), index); // Insert current node into path

    criticalPath[index].second = maxWeight; // Save this node's critical path weight as the sum of the path's weights

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
    std::pair<std::vector<unsigned int>, int> theCriticalPath;

    for (int i = 0; i < nodes.size(); i++) {
        if (visited[i]) {
            if (graphCriticalPaths[i].second > maxWeight) {
                maxWeight = graphCriticalPaths[i].second;
                theCriticalPath.first = graphCriticalPaths[i].first;
                theCriticalPath.second = maxWeight;
            }
            continue;
        }

        graphCriticalPaths = path_finder(graphCriticalPaths, visited, i);

        if (graphCriticalPaths[i].second > maxWeight) {
            maxWeight = graphCriticalPaths[i].second;
            theCriticalPath.first = graphCriticalPaths[i].first;
            theCriticalPath.second = maxWeight;
        }
    }

    // printf() debugging

    std::cout << "Critical path is:" << std::endl;
    for (auto node : theCriticalPath.first) {
        std::cout << nodes[node]->id << " -> ";
    }
    std::cout << "\nSum of nodes weight: " << theCriticalPath.second << std::endl;

}

// TODO: Função de busca em profundidade num grafo

 template class digraph<course>;