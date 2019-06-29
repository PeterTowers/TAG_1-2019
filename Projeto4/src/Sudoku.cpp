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

void Sudoku::solve(bool interactive){
  int last_missing = -1;
  unsigned int step = 0;

  unsigned int tolerance = 1;

  std::vector<int> guesses = {};

  // Repeat until the sudoku is solved
  while(!solved()){

    // The algorithm got stuck
    if (missing() == last_missing) tolerance++;
    else {
      tolerance = 1;
      last_missing = missing();
    };

    if (interactive){
      system("clear");
      std::cout << "Step: " << step << std::endl;
      std::cout << "Missing: " << missing() << std::endl;
      std::cout << "Solved? " << (solved() ? "yes" : "no") << std::endl << std::endl;
      print();
      std::cout << std::endl;
      step++;
    }
    


    // On each node
    for (unsigned int i = 0; i < nodes.size(); i++){

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
      if (interactive) {
        std::cout << "[" << i / 9 << "," << i % 9 << "]"
                  << " valid moves (" << guesses.size() << "): ";

        for (auto &&g : guesses)
          std::cout << g << " ";
        std::cout << std::endl;
      }

      // If there are no valid moves, the problem is invalid (or we made a mistake?)
      if (guesses.empty()){
        if (interactive) std::cout
          << "ERROR: Cell "
          << "[" << i / 9 << "," << i % 9 << "]"
          << " has no valid moves";

        return;
      }
      
      // Picking the cells with the least guess count
      if (guesses.size() <= tolerance){

        // If there is only one valid move, apply it
        if (tolerance == 1){
          nodes[i] = Cell(i, guesses[0]);
          break;
        }
        // If there are no cells with only one valid move (ambiguity)
        else {

          // For each possible guess
          for (unsigned int g = 0; g < guesses.size(); g++){
            Sudoku s(*this);          // Open a new solving frame
            s.nodes[i] = guesses[g];  // Where the current guess has been applied
            s.solve();                // Try to solve that frame

            // (interactive mode) If it's solvable using that guess, apply it
            if (s.solved()){
              nodes[i] = Cell(i, guesses[g]);
              break;
            }
          }
          
        }
      }
    }

    // Pause Frame
    if (interactive) getchar();
  }


    if (interactive) {
      system("clear");
      std::cout << "Solved in " << step << " steps" << std::endl;
      std::cout << std::endl;
      print();
    }
}