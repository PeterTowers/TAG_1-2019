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

    /* digraph::find_node_by_id
        Receives a node's id and locates its index in 'nodes' vector,
     */
    unsigned int find_node_by_id(unsigned int id);

    /* digraph::find_critical_path
        Finds the index of all the critical paths (according to the sum of their weights) and, if there's a tie, selects
        one with the most nodes. Returns the index of the critical path.
     */
    unsigned int find_critical_path(std::vector<std::pair<std::vector<unsigned int>, int>>);

    /* digraph::push
        Adds a node to the graph
        Receives:
          - A reference to the object to be inserted
      */
    void push(T*);

    /* digraph::print_adj
        Prints graph's adjacency list
      */
    void print_adj();

    /* digraph::print_ordered
        Prints a topologically-ordered version of the graph
      */
    void print_ordered(std::function<void(T)> = [](T a){ std::cout << a; });

    /* digraph::critical_path
        Calculates digraph's critical path using path_finder() and prints it
      */
    void critical_path();

    /* digraph::print_critical_path
        Prints a subgraph containing the critical path to a .dot file. Receives said critical path.
     */
    void print_critical_path(std::vector<unsigned int>);

    /* digraph::neighbors
        Receives
          - The index (position) of a node, relative to the digraph's internal array of nodes
        Returns:
          - A vector with the indices (positions) of the input node's
      */
    std::vector<unsigned int> neighbors(unsigned int);

    /* digraph::ordered
        Sorts the graph's nodes topologically. Arguments are optional,
          and are passed in to recursive calls rather than externally provided.

        Receives:
          - (optional) An array of booleans with the same length as the array of nodes,
              which tags each node (by array position) as permanently visited (true) or unvisited (false)
          - (optional) An array of nodes, which represents the partially constructed solution array.
        Returns:
          - An array of references to the graph's nodes, ordered as expected
      */
    std::vector<T*> ordered(std::vector<bool> visited = std::vector<bool>(),
                            std::vector<T*> output = std::vector<T*>());

    /* digraph::path_finder
        Recursively calculates a critical path for all nodes. If a course is disconnected, its path is set as itself and
        its weight, as the courses credits. Each course has its own critical path: itself or all nodes ahead of it.
        The critical path of a connected node is selected by the sum of course's credits, including the last one on the
        path.
      */
    std::vector<std::pair<std::vector<unsigned int>, int>> path_finder(
            std::vector<std::pair<std::vector<unsigned int>, int>> criticalPath, std::vector<bool> visited,
            unsigned int index);
};


