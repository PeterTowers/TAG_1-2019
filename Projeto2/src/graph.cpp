#include "../include/graph.hpp"
#include "../include/course.hpp"

// template <class T>
// std::vector<T*> digraph<T>::nodes() { return this.nodes };


void foo(){
  std::vector<int> vec({1, 2, 3, 4});

  for(int i = 0; i < vec.size(); i++)
    std::cout << vec[i] << std::endl;

  for(auto& c : vec)
    std::cout << c << std::endl;

};

template <class T>
void digraph<T>::push(T* value) {
    nodes.push_back(value);
}

template <class T>
bool digraph<T>::connect(unsigned int id1, unsigned int id2, std::function<unsigned int(T)> get_id){
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












// template <class T>
// bool digraph<T>::filter(std::function<bool(T)> f){
//   // TODO: Implement graph filtering
//   return this;
// }

// template <class T>
// digraph<T> digraph<T>::without(T* address){
//   // TODO: Implement graph filtering
//   auto target = nodes.find(nodes.begin(), nodes.end(), address)

//   return (target == nodes.end()
//     ? this
//     : digraph<T>(nodes, ));
// }


// template <class T>
// unsigned int digraph<T>::nodecount(){ return nodes.size() }


// std::vector<T> filter(std::vector<T> input, std::function<bool(T)> criteria){
//   std::vector<T> output = []

//   for(auto& element : input)
//     if (criteria(element) == true)
//       output.push_back(element);

//   return output;
// }


// TODO: Método que retorna as bordas partindo de um nó pelo índice
// TODO: Função de busca em profundidade num grafo
 template <class T>
std::vector<unsigned int> digraph<T>::neighbors(unsigned int i){
    std::vector<unsigned int> output;

    for(int i = 0; i < edges.size(); i++)
        if(edges[i].first == nodes[i])
            output.push_back(i);

        return output;
};

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

    if(std::find(output.begin(), output.end(), node) != output.end()) continue; // Node has been visited on current iteration

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
    output.push_back(node);
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



// template <class T>
// void digraph<T>::cp_edges(digraph<T>* origin) {
//     edges = origin->edges;
// }

// template<class T>
// digraph<T> digraph<T>::root_nodes() {
//     digraph<T> roots;
//     bool isRoot = true;

//     for (auto& node : nodes) {
//         for (auto& edge : edges)
//             if (node->id == edge.second->id) {
//                 isRoot = false;
//                 break;
//             }
//         if (isRoot)
//             roots.push(node);
//         else
//             isRoot = true;
//     }
//     return roots;
// }

 template class digraph<course>;