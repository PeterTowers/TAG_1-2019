#ifndef PROJETO_4_CELL_HPP
#define PROJETO_4_CELL_HPP

#include <iostream>
#include <vector>

class Cell {
private:
    int value;                          // Stores the value attributed to a cell. 0 means no value attributed
    std::vector<int> neighbors;         // Stores the index of a cell's neighbors in Sudoku's 'nodes' vector

    void neighbor_column(int index);    // Sets the neighbors inside the same COLUMN of the cell
    void neighbor_row(int index);       // Sets the neighbors inside the same ROW of the cell
    void local_neighbors(int index);    // Sets the remaining neighbors inside the same quadrant of the cell

public:
    /* Constructor method
     * Receives cell's index inside Sudoku's 'nodes' vector and sets its 'value' to 0, by default.
     * Calls methods to calculate and set the cell's neighbors
     */
    Cell(int index, int value = 0) : value(value) {

        neighbor_column(index);
        neighbor_row(index);
        local_neighbors(index);
    };
    /*  Destructor method
     *
     */
    ~Cell() {
        neighbors.clear();
    };

    // Method get_value() returns the cell's stored value
    int getValue();

    friend std::ostream& operator<<(std::ostream& os, Cell& cell){
      os << (cell.getValue() > 0 ? std::to_string(cell.getValue()) : " ");
      return os;
    }

    // Method get_neighbors() returns the cell's neighbors, in the form of its adjacency list
    std::vector<int> get_neighbors() { return neighbors; }
};


#endif //PROJETO_4_CELL_HPP
