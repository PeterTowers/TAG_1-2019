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
    ~Sudoku();

    bool valid_move(int index, int value);

    // Sudoku::solve - Iteratively solves the puzzle
    void solve(bool = false);

    // Sudoku::solved - Checks if the puzzle is solved
    bool solved();
    
    // Sudoku::print - Pretty-prints the sudoku as a matrix
    void print();

    // Sudoku::missing - Counts how many cells are missing until the puzzle is solved
    int missing();

    // Sudoku::generate - Generates a new playable board
    void generate();

    // Sudoku::clear_board() - Clears the board by setting all cell's values to -1
    void clear_board();

    // Sudoku::games() - Loads precoded games
    void games(int i);
};

#endif //PROJETO_4_SUDOKU_HPP