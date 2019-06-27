#ifndef PROJETO_4_CELL_HPP
#define PROJETO_4_CELL_HPP

#include <vector>

class Cell {
private:
    int value;
    std::vector<int> neighbors;

    void neighbor_column(int i);
    void neighbor_row(int i);

public:
    Cell(int i);
    ~Cell();
};


#endif //PROJETO_4_CELL_HPP
