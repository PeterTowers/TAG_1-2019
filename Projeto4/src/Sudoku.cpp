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
  // for (auto &&c : init)
  //   nodes.push_back(c);

  for (int i = 0; i < init.size(); i++)
    nodes.emplace_back(i, init[i]);
  

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

bool Sudoku::solved(){
  return missing() == 0;
}

int Sudoku::missing(){
  int i = 0;

  for (auto &&cell : nodes)
    if (cell.getValue() < 0)
      i++;

  return i;
}

void Sudoku::solve(){
  int last_missing = -1;
  int step = 0;

  int tolerance = 1;

  std::vector<int> guesses = {};

  // Repeat until the sudoku is solved
  while(!solved()){

    // The algorithm got stuck
    if (missing() == last_missing) tolerance++;
    else {
      tolerance = 1;
      last_missing = missing();
    };

    system("clear");
    std::cout << "Step: " << step << std::endl;
    std::cout << "Missing: " << missing() << std::endl;
    std::cout << "Solved? " << (solved() ? "yes" : "no") << std::endl << std::endl;
    print();
    std::cout << std::endl;
    step++;
    


    // On each node
    for (int i = 0; i < nodes.size(); i++){

      // Skip if cell is not empty
      if (nodes[i].getValue() > 0) continue;

      // Start a new frame if a cell has already been filled this frame
      if (missing() != last_missing) break;

      // Recalculate guesses
      guesses.clear();

      // Calculate valid moves within node
      for (int move = 1; move < SIDE + 1; move++)
        if (valid_move(i, move)) guesses.push_back(move);


      // Print valid moves
      std::cout << "[" << i / 9 << "," << i % 9 << "]"
                << " valid moves (" << guesses.size() << "): ";

      for (auto &&g : guesses)
        std::cout << g << " ";
      std::cout << std::endl;

      // If there are no valid moves, the problem is invalid (or we made a mistake?)
      if (guesses.empty()){
        std::cout << "ERROR: Cell "
                  << "[" << i / 9 << "," << i % 9 << "]"
                  << " has no valid moves";
        return;
      }
      
      // If there is only one valid move, apply it
      if (guesses.size() <= tolerance){
        nodes[i] = Cell(i, guesses[0]);
        break;
      }
    }

    // Pause Frame
    getchar();
  }
}