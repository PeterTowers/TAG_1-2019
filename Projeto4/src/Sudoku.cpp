#include "../include/Sudoku.hpp"

#define SIDE 9


Sudoku::Sudoku(){

  // Example                  0    1    2    3    4    5    6    7    8
  std::vector<int> init = {  6,   7,   -1,  -1,  -1,  -1,  -1,  8,   -1  // 0
                          ,  -1,  -1,  4,   2,   -1,  6,   -1,  -1,  3   // 1
                          ,  -1,  -1,  2,   7,   -1,  1,   6,   9,   -1  // 2
                          ,  -1,  -1,  1,   -1,  -1,  3,   -1,  6,   -1  // 3
                          ,  9,   -1,  -1,  1,   -1,  5,   -1,  -1,  7   // 4
                          ,  -1,  3,   -1,  9,   -1,  -1,  5,   -1,  -1  // 5
                          ,  -1,  1,   3,   6,   -1,  9,   8,   -1,  -1  // 6
                          ,  5,   -1,  -1,  8,   -1,  2,   1,   -1,  -1  // 7
                          ,  -1,  2,   -1,  -1,  -1,  -1,  -1,  3,   9   // 8
                          };

  // Edition should come here
  for (auto &&c : init)
    nodes.push_back(c);

  return;
}

/*  valid_move()
 *  Receives: nodes' index (where you wanna place a number) and the value you want to place there
 *  Returns: 'true' if a move is valid or 'false' if not.
 */
bool Sudoku::valid_move(int index, int value) {
    std::vector<int> neighbors = nodes[index].get_neighbors();  // Stores a given cell's neighbors

    // Iterates through the cell's neighbors to find a matching value
    for (auto n : neighbors)
        if (value == nodes[n].getValue())  // If the input was placed elsewhere, the move is not valid
            return false;

    // If the input wasn't placed inside a given cell's neighbors, the move is valid
    return true;
}

Sudoku::~Sudoku(){
  nodes.clear();
  edges.clear();
}

void Sudoku::print(){
  int line = 0;
  int column = 0;


  for(int line = 0; line < SIDE; line++){
    std::cout << ' ';

    // Every third line: Print a line
    if (line > 0 && line % 3 == 0){
      // std::cout << "-";

      // Iterate columns
      for (int c = 0; c < SIDE; c++){
        if(c > 0 && c % 3 == 0) std::cout << "+ "; // Print a divisor between clusters

        std::cout << "- ";
      }


      // Skip a line;
      std::cout << "\n ";
    }

    // Print Row
    for(int column = 0; column < SIDE; column++){
      auto node = nodes[SIDE * line + column];

      if(column > 0 && column%3 == 0) std::cout << "| "; // Print a divisor between clusters

      std::cout << node;

      std::cout << ' ';
    }

    std::cout << '\n';
  }

  return;
}