#include "../include/sudoku.hpp"

#define SIDE 9


// Dummy Init
Sudoku::Sudoku(){
  for(int i = 0; i < SIDE * SIDE; i++)
    nodes.push_back(-1);


  // Example -  n, x, y
  std::vector<Cell> init = { { 6 } // 1st line
              , { 7 }
              , { 8 }
              , { 4 } // 2nd line
              , { 2 }
              , { 6 }
              , { 3 }
              , { 2 } // 3rd line
              , { 7 }
              , { 1 }
              , { 6 }
              , { 9 }
              , { 1 } // 4th line
              , { 3 }
              , { 6 }
              , { 9 } // 5th line
              , { 1 }
              , { 5 }
              , { 7 }
              , { 3 } // 6th line
              , { 9 }
              , { 5 }
              , { 1 } // 7th line
              , { 3 }
              , { 6 }
              , { 9 }
              , { 8 }
              , { 5 } // 8th line
              , { 8 }
              , { 2 }
              , { 1 }
              , { 2 } // 9th line
              , { 3 }
              , { 9 }
              };

  // Edition should come here

  return;






  return;
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

      if (node < 0) std::cout << 'x';
      else std::cout << node;

      std::cout << ' ';
    }

    std::cout << '\n';
  }

  return;
}