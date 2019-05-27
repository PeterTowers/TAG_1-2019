#pragma once
#include <iostream>
#include <vector>

#include "Edge.hpp"
#include "Node.hpp"

template <class T> class Matrix {
  private:
    std::vector<std::vector<int>> cells;

  public:
    Matrix(std::vector<std::vector<int>> cells) : cells(cells) {};
    Matrix(std::vector<Edge<T>> edges, std::vector<Node> nodes);

    // Checks whether the passed indices are within the matrix's range
    bool contains(const unsigned int i, const unsigned int j);

    // Sets the weight of an edge
    void set(Edge<T> edge);

    // Access (getter) operators
    int operator()(const unsigned int i, const unsigned int j) {
      return contains(i, j) ? cells[i][j] : -1;
    };
    int operator()(Edge<T> edge) { return this[edge.from(), edge.to()]; };

    void push(Node& node){};
};