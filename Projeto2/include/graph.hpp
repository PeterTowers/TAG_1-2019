#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>

template <class T> class digraph
{
private:
    std::vector<T*> nodes;
    std::vector<std::pair<T*, T*>> edges;

public:
    digraph() : nodes(), edges() { };
    ~digraph() {};

    bool connect(unsigned int,
                 unsigned int,
                 std::function<unsigned int(T)> get_id = [](T a){ return a; });
    void print_adj();
    void push(T*);
    void cp_edges(digraph<T>* origin);
    digraph<T> root_nodes();
};


