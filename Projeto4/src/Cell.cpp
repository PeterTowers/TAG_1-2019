#include "../include/Cell.hpp"

/*  neighbor_row()
 *  Receives: the cell's index
 *  Uses the cell's index to calculate the index of all the other cell's that are in the same row as itself.
 *  Places this value inside cell's 'neighbors' vector.
 */
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

/*  neighbor_column()
 *  Receives: the cell's index
 *  Uses the cell's index to calculate the index of all the other cell's that are in the same column as itself.
 *  Places this value inside cell's 'neighbors' vector.
 */
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
/*  local_neighbors()
 *  Receives: cell's index                                                                                      TL|TM|TR
 *  Calculates same quadrant neighbors's indexes that aren't in cell's column or row.                           --+--+--
 *  There are 9 possible position for a cell to be within its own quadrant, displayed on the right:             ML|MM|MR
 *  Using the formulas below, we can calculate the cell's position in its quadrant and then calculate its       --+--+--
 *  neighbors position inside the same quadrant from the cell's index.                                          BL|BM|BR
 */
void Cell::local_neighbors(int index) {
    int x = (index % 9)%3;  // Calculates cell's X position inside its own quadrant
    int y = (index / 9)%3;  // Calculates cell's Y position inside its own quadrant

    if (x == 0) {           // Cell is in a left position
        if (y == 0) {       // Cell is in TL (top-left) position
            neighbors.push_back(index + 10);    // Same quadrant neighbors are located in MM, MR, BM and BR positions.
            neighbors.push_back(index + 11);    // MM and BR are in the main diagonal, so +10 and +20 apart from cell's
            neighbors.push_back(index + 20);    // index. MR and BM are 1 position after and before, respectively, the
            neighbors.push_back(index + 19);    // main diagonal, so +11 and +19 from cell's index.
        }
        else if (y == 1) {  // Cell is in ML (middle-left) position
            neighbors.push_back(index - 8);     // Neighbors are located in TM, TR, BM and BR positions. TM and TR are
            neighbors.push_back(index - 7);     // -8 and -7 apart, BM and BR, +10, +11.
            neighbors.push_back(index + 10);
            neighbors.push_back(index + 11);
        }
        else {              // The only other possible value for y is 2, which means cell's in BL (bottom-left) position
            neighbors.push_back(index - 8);     // Neighbors are located in TM, TR, MM and MR positions. MM and MR are
            neighbors.push_back(index - 7);     // -8 and -7 apart. TM and TR, -16 and -17.
            neighbors.push_back(index - 16);
            neighbors.push_back(index - 17);
        }
    }
    else if (x == 1) {      // Cell is in a middle position
        if (y == 0) {       // Cell is in TL (top-middle) position
            neighbors.push_back(index + 8);     // Neighbors are located in ML, MR, BL and BR positions. ML and MR are
            neighbors.push_back(index + 10);    // +8 and +10 apart, BL and BR, +17, +19.
            neighbors.push_back(index + 17);
            neighbors.push_back(index + 19);
        }
        else if (y == 1) {  // Cell is in MM (middle-middle) position
            neighbors.push_back(index - 10);    // Neighbors are located in TL, TR, BL and BR positions, which are in
            neighbors.push_back(index - 8);     // the main and opposite diagonals. TL is -10 apart, TR is -8, BL, +8
            neighbors.push_back(index + 8);     // and BR, +10.
            neighbors.push_back(index + 10);
        }
        else {              // Cell is in BM (bottom-middle) position
            neighbors.push_back(index - 10);    // Neighbors are located in TL, TR, ML and MR positions. ML and MR are
            neighbors.push_back(index - 8);     // -10 and -8 apart. TL and TR, -19 and -17.
            neighbors.push_back(index - 19);
            neighbors.push_back(index - 17);
        }
    }
    else {                  // Cell is in a right position
        if (y == 0) {       // Cell is in TR (top-right) position
            neighbors.push_back(index + 7);     // Neighbors are located in ML, MM, BL and BM positions. ML and MM are
            neighbors.push_back(index + 8);     // +7 and +8 apart, BL and BM, +17, +18.
            neighbors.push_back(index + 17);
            neighbors.push_back(index + 18);
        }
        else if (y == 1) {  // Cell is in MR (middle-right) position
            neighbors.push_back(index - 11);    // Neighbors are located in TL, TM, BL and BM positions. TL and TM are
            neighbors.push_back(index - 10);    // -11 and -10, respectively, apart. BL and BM, +7 and +8.
            neighbors.push_back(index + 7);
            neighbors.push_back(index + 8);
        }
        else {              // Cell is in BR (bottom-right) position
            neighbors.push_back(index - 20);    // Neighbors are located in TL, TM, ML and MM positions. TL and TM are
            neighbors.push_back(index - 19);     // -20 and -19 and -8 apart. ML and MM, -11 and -10.
            neighbors.push_back(index - 11);
            neighbors.push_back(index - 10);
        }
    }
}

int Cell::getValue(){
  return value;
}

Cell::~Cell(){};