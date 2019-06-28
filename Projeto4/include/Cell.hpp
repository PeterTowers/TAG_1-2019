#ifndef PROJETO_4_CELL_HPP
#define PROJETO_4_CELL_HPP

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
};


#endif //PROJETO_4_CELL_HPP
