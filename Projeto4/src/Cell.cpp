#include "../include/Cell.hpp"

Cell::Cell(int index) {
    value = index;

    neighbor_column(index);
    neighbor_row(index);

}

void Cell::neighbor_row(int index) {
    int y = index / 9;  // Calculates a cell's ROW

    // This clause calculates the cell's COLUMN, in order to initialize the position of the neighbors in its ROW
    switch (index % 9) {
        // Cell is located in row 0
        case 0 :
            for (int j = 1; j < 9; j++)
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);

            break;

        // Cell is located in row 1
        case 1 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 1)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 2
        case 2 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 2)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 3
        case 3 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 3)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 4
        case 4 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 4)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 5
        case 5 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 5)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 6
        case 6 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 6)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 7
        case 7 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 7)
                    continue;
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);
            }
            break;

        // Cell is located in row 8
        case 8 :
            for (int j = 0; j < 8; j++)
                // The cell's row neighbors are located in the position (j + 9*y)
                neighbors.push_back(j + 9*y);

            break;
    }
}

void Cell::neighbor_column(int index) {
    int x = index % 9;  // Calculates a cell's COLUMN

    // This clause calculates the cell's ROW, in order to initialize the position of the neighbors in its COLUMN
    switch (index / 9) {
        // Cell is located in row 0
        case 0 :
            for (int j = 1; j < 9; j++) {
                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 1
        case 1 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 1)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 2
        case 2 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 2)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 3
        case 3 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 3)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 4
        case 4 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 4)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 5
        case 5 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 5)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 6
        case 6 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 6)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 7
        case 7 :
            for (int j = 0; j < 9; j++) {
                // Since a cell is not a neighbor of itself, we jump it
                if (j == 7)
                    continue;

                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;

        // Cell is located in row 8
        case 8 :
            for (int j = 0; j < 8; j++) {
                // The cell's column neighbors are located in the position (j*9 + x)
                neighbors.push_back(j*9 + x);
            }
            break;
    }
}