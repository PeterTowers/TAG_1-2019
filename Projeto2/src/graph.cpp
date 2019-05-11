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

// Method neighbors() receives a vertex's id and returns its neighbors' ids
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

template<class T>
std::vector<T *> digraph<T>::critical_path(int weightSum, int auxWeight, int index, int pos,
                                           std::vector<unsigned int> criticalPath, std::vector<int> auxPath) {
    // Checks if graph has edges. pos == 0 means it'll check only on the first method call
    if (index == 0 && edges.empty()) {
        std::cout << "Error: graph has no edges." << std::endl;
        exit(-666); // TODO: just quit method instead of ending the whole program
    }

    if (nodes[index] == nodes.end());   // TODO: end recursion

    auto neighborhood = neighbors(nodes[index]->id);

    if (neighborhood.empty());   // TODO: end recursion

    auxWeight += nodes[index]->credits;

    for (auto neighbor : neighborhood) {
        int i = 0;
        for (i; i < nodes.size(); i++)
            if (edges[neighbor].second() == nodes[i])
                break;
    }

}

// TODO: Função de busca em profundidade num grafo

 template class digraph<course>;