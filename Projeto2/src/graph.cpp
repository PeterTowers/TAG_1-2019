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
void digraph<T>::print_adj(){
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


template <class T>
unsigned int digraph<T>::nodecount(){ return nodes.size() }


std::vector<T> filter(std::vector<T> input, std::function<bool(T)> criteria){
  std::vector<T> output = []

  for(auto& element : input)
    if (criteria(element) == true)
      output.push_back(element);

  return output;
}


// TODO: Método que retorna as bordas partindo de um nó pelo índice
// TODO: Função de busca em profundidade num grafo
std::vector<T*> dfs()

template <class T>
std::vector<T*> digraph<T>::
  ordered(std::vector<T*>                          visited = [],
          std::vector<std::pair<T*, unsigned int>> costs   = [],
          std::function<unsigned int(T)>           weight  = [](T x){ return x; }) {


  std::vector<T*> remaining = filter(nodes, [](T visited){ return node != visited });

  if(remaining.empty()) return remaining;



  // 1. Chamar dfsTodosVertices em G para computar f[v] para cada vértice v
  for(auto& node : remaining){
    if(perm.find(node) != perm.end()) continue; // Node has been visite

    // 2. Se G contém uma aresta retorno (v, w) (i.e., se f[w] > f[v]) , reportar erro ;
    for(auto& t : temp){
      
    }
  
    // 3. Caso contrário, com cada vértice terminado anexe em uma lista; // ou push em pilha
    
    // 4. Retornar a lista; // lista é uma ordenação topológica válida
    while(perm.size() < T->nodecount()){

    }
  }

  return list<T>;
}



template class digraph<course>;