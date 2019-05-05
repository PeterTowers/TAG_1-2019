#include "../include/graph.hpp"
#include "../include/course.hpp"

// template <class T>
// std::vector<T*> digraph<T>::nodes() { return this.nodes };

template <class T>
void digraph<T>::push(T* value) {
    nodes.push_back(value);
}

template <class T>
bool digraph<T>::connect(unsigned int id1, unsigned int id2, std::function<unsigned int(T)> get_id){
    course *c1 = nullptr, *c2 = nullptr;

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
                std::cout << edge.first->id << ' ';

        std::cout << std::endl;
    }
}

template class digraph<course>;