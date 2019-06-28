#ifndef PROJETO_4_SUDOKU_HPP
#define PROJETO_4_SUDOKU_HPP

#include <iostream>
#include <vector>

#include "../include/Cell.hpp"

class Sudoku {
private:
    std::vector<Cell> nodes;
    std::vector<int> edges;

public:
    Sudoku();
    ~Sudoku() {};

    bool valid_move(int index, int value);
    void solve();
    void print();
};

#endif //PROJETO_4_SUDOKU_HPP