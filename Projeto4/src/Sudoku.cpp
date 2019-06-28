#include "../include/Sudoku.hpp"

// Dummy Init
Sudoku::Sudoku(){
  for(int i = 0; i < 9*9; i++)
    nodes.push_back(Cell(0));

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
        if (value == nodes[n].get_value())  // If the input was placed elsewhere, the move is not valid
            return false;

    // If the input wasn't placed inside a given cell's neighbors, the move is valid
    return true;
}

void Sudoku::print(){
  int line = 0;
  int column = 0;


  for(int line = 0; line < 9; line++){

    // Every third line: Print a line
    if (line%3 == 0){
      std::cout << "-";

      // Iterate columns
      for (int c = 0; c < 9; c++){
        std::cout << "--";
      }

      if(column%3 == 0) std::cout << "| "; // Print a divisor between clusters

      // Skip a line;
      std::cout << '\n';
    }

    // Print Row
    for(int column = 0; column < 9; column++){
      auto node = nodes[10*line + column];

      if(column%3 == 0) std::cout << "| "; // Print a divisor between clusters

      std::cout << (node.get_value() < 0 ? ' ' : node.get_value()); // Print a blank space if the node has not been set
    }

    std::cout << '\n';
  }

  return;
}