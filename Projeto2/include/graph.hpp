#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <stack>

template <class T> class digraph {
private:
    std::vector<T*> nodes;
    std::vector<std::pair<T*, T*>> edges;

public:
    // digraph() : nodes(), edges() { };
    digraph(std::vector<T*> nodes = std::vector<T*>(), std::vector<std::pair<T*, T*>> edges = std::vector<std::pair<T*, T*>>())
      : nodes(nodes),
        edges(edges) { };

    ~digraph() {};


    // Connects two nodes, by id. Requires a function that determines the unique id of a given node
    bool connect(unsigned int, // source node
                 unsigned int, // targed node
                 std::function<unsigned int(T)> get_id = [](T a){ return a; });

    // Adds a node to the graph
    void push(T*);

    // digraph<T> filter(std::function<bool(T)>); // Returns the subgraph that excludes nodes for which the given function returns false


//    digraph<T> without(T*); // Returns the graph without the given element
    std::vector<T*> ordered(std::vector<bool> visited = std::vector<bool>(), std::vector<T*> output = std::vector<T*>());

    // TODO: implement
    std::vector<unsigned int> neighbors(unsigned int);

    unsigned int nodecount();
    void print_ordered(std::function<void(T)> = [](T a){ std::cout << a;; }); // Prints a topologically-ordered version of the graph
    void print_adj();     // Prints the graph's adjacency list
    
    // void cp_edges(digraph<T>* origin);
    // digraph<T> root_nodes();
};


