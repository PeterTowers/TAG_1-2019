#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <stack>


#include "../include/Edge.hpp"
#include "../include/Node.hpp"

// Class for a polymorphic graph
class Graph {
private:
    std::vector<Node> nodes; // Vector for all nodes in graph
    std::vector<Edge> edges;  // Vector for all the edges between nodes in graph
    bool directed;

public:
    // Constructor method. Initializes both 'nodes' and 'edges' to { } (empty set) by default
    Graph(std::vector<Node> nodes = std::vector<Node>(),
          std::vector<Edge> edges = std::vector<Edge> (),
          bool                 directed = false)
      : nodes(nodes),
        edges(edges),
        directed(directed) { };

    // Destructor method
    ~Graph() { nodes.clear(); edges.clear(); };

    // Connects two nodes, by id. Requires a function that determines the unique id of a given node
    /* graph::connect
        Receives two node ids, searches for the requested ids and
     */
    bool connect(unsigned int, unsigned int, int = 0);

    /* graph::connected
        Receives two node ids, returns whether these nodes are connected
     */
    bool connected(unsigned int, unsigned int);

    /* graph::find_node_by_id
        Receives a node's id and locates its index in 'nodes' vector
        Returns -1 if not found
     */
    int find_node_by_id(unsigned int id);

    /* graph::find_critical_path
        Finds the index of all the critical paths (according to the sum of their weights) and, if there's a tie, selects
        one with the most nodes. Returns the index of the critical path.
     */
    unsigned int find_critical_path(std::vector<std::pair<std::vector<unsigned int>, int>>);

    /* graph::push
        Adds a node to the graph
        Receives:
          - A reference to the object to be inserted
      */
    void push(Node&);

    /* graph::print_adj
        Prints graph's adjacency list
      */
    void print_adj();

    /* graph::print_ordered
        Prints a topologically-ordered version of the graph
      */
    void print_ordered(std::function<void(Node)> = [](Node node){ std::cout << node; });

    

    void inspect(std::function<void(Node)> = [](Node node){ std::cout << node.get_id(); }, std::string = ", ");

    /* graph::critical_path  
        Calculates graph's critical path using path_finder() and prints it
      */
    void critical_path();

    /* graph::print_critical_path
        Prints a subgraph containing the critical path to a .dot file. Receives said critical path.
     */
    void print_critical_path(std::vector<unsigned int>);

    /* graph::neighbors
        Receives
          - The index (position) of a node, relative to the graph's internal array of nodes
        Returns:
          - A vector with the indices (positions) of the input node's
      */
    std::vector<unsigned int> neighbors(unsigned int);

    /* graph::ordered
        Sorts the graph's nodes topologically. Arguments are optional,
          and are passed in to recursive calls rather than externally provided.

        Receives:
          - (optional) An array of booleans with the same length as the array of nodes,
              which tags each node (by array position) as permanently visited (true) or unvisited (false)
          - (optional) An array of nodes, which represents the partially constructed solution array.
        Returns:
          - An array of references to the graph's nodes, ordered as expected
      */
    std::vector<Node> ordered(std::vector<bool> visited = std::vector<bool>(),
                            std::vector<Node> output = std::vector<Node>());

    /* graph::path_finder
        Recursively calculates a critical path for all nodes. If a course is disconnected, its path is set as itself and
        its weight, as the courses credits. Each course has its own critical path: itself or all nodes ahead of it.
        The critical path of a connected node is selected by the sum of course's credits, including the last one on the
        path.
      */
    std::vector<std::pair<std::vector<unsigned int>, int>> path_finder(
            std::vector<std::pair<std::vector<unsigned int>, int>> criticalPath, std::vector<bool> visited,
            unsigned int index);
};


