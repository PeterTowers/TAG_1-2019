

class Cell {
  int value;
  std::vector<int> neighbors;
}

class Sudoku {
  private:
    std::vector<int> nodes;
    std::vector<int> edges;

  public:
    Sudoku();
    ~Sudoku();
    void solve()
    void print();
}