#ifndef PROJETO_4_CELL_HPP
#define PROJETO_4_CELL_HPP

#include <iostream>
#include <vector>

class Cell {
private:
    int value;
    std::vector<int> neighbors;

    void neighbor_column(int index);
    void neighbor_row(int index);
    void local_neighbors(int index);

public:
    Cell(int index);
    ~Cell();

    int getValue();

    friend std::ostream& operator<<(std::ostream& os, Cell& cell){
      os << (cell.getValue() > 0 ? std::to_string(cell.getValue()) : " ");
      return os;
    }
    std::vector<int> get_neighbors() { return neighbors; }
};


#endif //PROJETO_4_CELL_HPP
