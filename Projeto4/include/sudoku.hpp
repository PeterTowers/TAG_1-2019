#include <iostream>
#include <vector>

class Cell {
  int value;
  std::vector<int> neighbors;

  public:
    Cell(int value = -1) : value(value) {};
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