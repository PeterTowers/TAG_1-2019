#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <functional>


template <class T> class digraph
{
private:
    std::vector<T*> nodes;
    std::vector<std::pair<T*, T*>> edges;

public:
    // digraph() : nodes(), edges() { };
    digraph(std::vector<T*> nodes = [], std::vector<std::pair<T*, T*>> edges = [])
      : nodes(nodes),
        edges(edges) { };

    ~digraph() {};

    bool connect(unsigned int,
                 unsigned int,
                 std::function<unsigned int(T)> get_id = [](T a){ return a; });

    void push(T*);

    // digraph<T> filter(std::function<bool(T)>); // Returns the subgraph that excludes nodes for which the given function returns false

    digraph<T> without(T*); // Returns the graph without the given element
    std::vector<T*> ordered();

    unsigned int nodecount();
    void print_ordered(); // Prints a topologically-ordered version of the graph
    void print_adj();     // Prints the graph's adjacency list
};


