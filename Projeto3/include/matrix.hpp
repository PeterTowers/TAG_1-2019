#pragma once
#include <iostream>
#include <vector>

#include "edge.hpp"
#include "node.hpp"

template <class T> class matrix {
  private:
    std::vector<std::vector<int>> cells;

  public:
    matrix(std::vector<std::vector<int>> cells) : cells(cells) {};
    matrix(std::vector<edge<T>> edges, std::vector<node<T>> nodes);

    // Checks whether the passed indices are within the matrix's range
    bool contains(const unsigned int i, const unsigned int j);

    // Sets the weight of an edge
    void set(edge<T> edge);

    // Access (getter) operators
    int operator()(const unsigned int i, const unsigned int j) {
      return contains(i, j) ? cells[i][j] : -1;
    };
    int operator()(edge<T> edge) { return this[edge.from(), edge.to()]; };
};