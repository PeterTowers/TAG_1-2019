#include "../include/graph.hpp"
#include "../include/course.hpp"

// template <class T>
// std::vector<T*> digraph<T>::nodes() { return this.nodes };

template <class T>
void digraph<T>::push(T* value) {
    nodes.push_back(value);
}

template <class T>
bool digraph<T>::connect(unsigned int id1, unsigned int id2, std::function<unsigned int(T)> get_id) {
    T *c1 = nullptr, *c2 = nullptr;

    for(auto&& c : nodes){
        if (get_id(*c) == id1) c1 = c;
        if (get_id(*c) == id2) c2 = c;
    }

    if (c1 == nullptr || c2 == nullptr) return false;

    edges.push_back({ c1, c2 });
    // edges.push_back(std::pair<course*, course*>(c1, c2));

    return true;
}

template <class T>
void digraph<T>::print_adj() {
    std::cout << "[print_adj] Printing adjacency list: " << std::endl;

    for (auto& node : nodes){
        std::cout << "[print_adj] "
                  << node->id
                  << " -> ";

        for (auto& edge : edges)
            if (edge.first->id == node->id)
                std::cout << edge.second->id << ' ';

        std::cout << std::endl;
    }
}

template <class T>
std::vector<unsigned int> digraph<T>::neighbors(unsigned int i) {
    std::vector<unsigned int> output;

    for(int i = 0; i < edges.size(); i++)
        if(edges[i].first == nodes[i])
            output.push_back(i);

        return output;
}

template <class T>
std::vector<T*> digraph<T>::ordered(std::vector<bool> visited, std::vector<T*> output) {
  
  // Initialize visited array
  if (visited.empty())
    for(auto node : nodes)
      visited.push_back(false);

  // 1. Chamar dfsTodosVertices em G para computar f[v] para cada vértice v
  for (int i = 0; i < nodes.size(); i++){
    // if(output.count() == nodes.count()) break; // All nodes have been visited

    visited[i] = true;
    auto node = nodes[i];
    output.push_back(node);

    // Node has been visited on current iteration
    if(std::find(output.begin(), output.end(), node) != output.end()) continue;

    for(auto neighbor : neighbors(i)){
      
      // 2. Se G contém uma aresta retorno (v, w) (i.e., se f[w] > f[v]) , reportar erro ;  
      if(visited[neighbor]){
        std::cout << "[digraph::ordered] error: found cycle (" << i << ',' << neighbor << ')' << std::endl;
        exit(-1);
      }

      // Neighbor has been stacked, move on to next neighbor
      if(std::find(output.begin(), output.end(), node) == output.end())
        for(auto stacked : ordered(visited, output))
          output.push_back(stacked);
    }

  }

  return output;
}

template <class T>
void digraph<T>::print_ordered(std::function<void(T)> print_node){
  auto ordered = this->ordered();

  for (int i = 0; i < ordered.size(); i++){
    std::cout << "node: ";
    print_node(*nodes[i]);
    std::cout << std::endl;
  }
}

template <class T>
std::vector<T*> digraph<T>::critical_path(std::vector<bool> visited, std::vector<T*> output) {

}

// TODO: Função de busca em profundidade num grafo

 template class digraph<course>;