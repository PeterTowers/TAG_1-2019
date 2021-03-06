#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <stack>

// Class for a polymorphic digraph
template <class T> class digraph {
private:
    std::vector<T*> nodes;                  // Vector for all nodes in digraph
    std::vector<std::pair<T*, T*>> edges;   // Vector for all the edges between nodes in digraph

public:
    // digraph() : nodes(), edges() { };    // TODO: cleanup
    // Constructor method. Initializes both 'nodes' and 'edges' to { } (empty set) by default
    digraph(std::vector<T*> nodes = std::vector<T*>(),
            std::vector<std::pair<T*, T*>> edges = std::vector<std::pair<T*, T*>>())
      : nodes(nodes),
        edges(edges) { };

    // Destructor method
    ~digraph() { };


    // Connects two nodes, by id. Requires a function that determines the unique id of a given node
    bool connect(unsigned int, // source node
                 unsigned int, // targed node
                 std::function<unsigned int(T)> get_id = [](T a){ return a; });

    // Adds a node to the graph
    void push(T*);

    // Prints graph's adjacency list
    void print_adj();

    // Prints a topologically-ordered version of the graph
    void print_ordered(std::function<void(T)> = [](T a){ std::cout << a; });

    // Receives a vertex's id and returns its neighbors' ids
    // Retorna os ids dos vértices adjacentes ao vértice cujo id foi passado para o método
    std::vector<unsigned int> neighbors(unsigned int);

    // Topological sort
    std::vector<T*> ordered(std::vector<bool> visited = std::vector<bool>(),
                            std::vector<T*> output = std::vector<T*>());

    // Returns graph's critical path
    std::vector<T*> critical_path(std::vector<bool> visited = std::vector<bool>(),
                                  std::vector<T*> output = std::vector<T*>());

    // TODO: cleanup ------------------------------------------------------------------------------------------
    unsigned int node_count();

//    digraph<T> filter(std::function<bool(T)>); // Returns the subgraph that excludes nodes for which the given function returns false
//    digraph<T> without(T*); // Returns the graph without the given element

};


