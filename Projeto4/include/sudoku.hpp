#include <iostream>
#include <vector>

class Cell {
  std::vector<int> neighbors;

  public:
    Cell(int value = -1) : value(value) {};
    int value;

};

class Sudoku {
  private:
    std::vector<int> nodes;
    std::vector<int> edges;

  public:
    Sudoku();
    ~Sudoku();
    void solve();
    void print();
};