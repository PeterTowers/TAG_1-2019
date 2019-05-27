#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "Edge.hpp"
#include "Node.hpp"

template <class T, class U> class Matrix {
  private:
    std::vector<std::vector<int>> cells;

    std::vector<T> left;
    std::vector<U> right;

  public:
    Matrix() : cells({}), left({}), right({}) {};
    // matrix(Matrix<T,U> data)
    //   : cells(data.cells),
    //     left(data.left),
    //     right(data.right) {};

    Matrix(std::vector<std::vector<int>> cells) : cells(cells) {};
    Matrix(std::vector<T>, std::vector<U>, std::vector<Edge> = {});

    // Indicates whether the passed indices are within the matrix's range
    bool contains(const unsigned int i, const unsigned int j);

    // Indicates whether the matrix's left or right group are empty
    bool empty();

    // Sets the weight of an edge
    void set(Edge edge);

    void push(T); // Push a new row
    void push(U); // Push a new column

    // Clones itself, except for the specified rows and columns
    Matrix<T,U> without(std::vector<unsigned int> = {}, std::vector<unsigned int> = {});

    // Clones itself, except for rows and columns which do not comply to the selector predicate
    Matrix<T,U> filter(std::function<bool(std::vector<int>)> = [](int x){ return false; }, bool = true);

    // Clones itself, swapping rows and columns
    Matrix<U,T> flipped();

    /* Returns a version of itself where every row and column is subtracted
      to the point where the minimum value is zero.
    */
    Matrix<T,U> minimized(bool = true);

    // Calculates the optimal graph pairing
    std::vector<Edge> pairing();

    // Returns zero-weighed edges
    std::vector<Edge> zeroes();

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
    void inspect(std::function<void(Node)> = [](Node node){ std::cout << node.get_id(); });

    // Cell getter operator overload. Usage: matrix(edge);
    int operator()(Edge edge) { return this->cells[edge.from()][edge.to()]; };
};