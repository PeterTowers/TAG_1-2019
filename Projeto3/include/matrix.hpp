#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "edge.hpp"
#include "node.hpp"

template <class T> class matrix {
  private:
    std::vector<std::vector<int>> cells;

    std::vector<node<T>> left;
    std::vector<node<T>> right;

  public:
    matrix() : cells({}), left({}), right({}) {};
    // matrix(matrix<T> data)
    //   : cells(data.cells),
    //     left(data.left),
    //     right(data.right) {};

    matrix(std::vector<std::vector<int>> cells) : cells(cells) {};
    matrix(std::vector<node<T>>, std::vector<node<T>>, std::vector<edge<T>> = {});

    // Indicates whether the passed indices are within the matrix's range
    bool contains(const unsigned int i, const unsigned int j);

    // Indicates whether the matrix's left or right group are empty
    bool empty();

    // Sets the weight of an edge
    void set(edge<T> edge);

    // Sets the weight of an edge
    void push(node<T>, bool = false); // TODO: implement

    // Clones itself, except for the specified rows and columns
    matrix<T> without(std::vector<unsigned int> = {}, std::vector<unsigned int> = {});

    // Clones itself, except for rows and columns which do not comply to the selector predicate
    matrix<T> filter(std::function<bool(std::vector<int>)> = [](int x){ return false; }, bool = true);

    // Clones itself, swapping rows and columns
    matrix<T> flipped();

    /* Returns a version of itself where every row and column is subtracted
      to the point where the minimum value is zero.
    */
    matrix<T> minimized();

    // Calculates the optimal graph pairing
    std::vector<edge<T>> pairing();

    // Returns zero-weighed edges
    std::vector<edge<T>> zeroes();

    /* Returns the minimum value within a line, unless 'flipped' is set to true,
        in which case it returns the minimum value within column
    */
    unsigned int minimum(unsigned int, bool = false);

    // Getter function
    std::vector<std::vector<int>> rows();

    // Cell getter operator. Usage: matrix(i, j);
    int operator()(const unsigned int i, const unsigned int j) {
      return contains(i, j)
        ? cells[i][j]
        : -1;
    };

    // Cell getter operator overload. Usage: matrix(edge);
    int operator()(edge<T> edge) { return this->cells[edge.from()][edge.to()]; };

    // Row getter operator. Usage: matrix[i]
    std::vector<int> operator[](const unsigned int i) {
      return contains(i, 0)
        ? cells[i]
        : std::vector<int>();
    };

    // Column getter operator. Usage: matrix | j
    std::vector<int> operator|(const unsigned int j) {
      std::vector<int> result = {};

      if (contains(0, j))
        std::transform(cells.begin(), cells.end(), result.begin(),
              [=](std::vector<int> row){ return row[j]; } );

      return result;
    };

    // Prints data in human-readable format
    void inspect(std::function<void(node<T>)> = [](node<T> node){ std::cout << node.id; });

    // Cell-setting operator. Usage: matrix = edge
//    void operator=(std::vector<edge<T>> edges) { for (auto& edge : edges) set(edge); }
};