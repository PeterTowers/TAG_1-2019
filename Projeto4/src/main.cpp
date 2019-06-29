#include <iostream>
#include "../include/Sudoku.hpp"
#include "../include/Cell.hpp"

int main(){
  Sudoku s;

  system("clear");

  s.solve(true);

  return 0;
}