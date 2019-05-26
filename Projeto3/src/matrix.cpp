#include "../include/matrix.hpp"

template<class T>
matrix<T>::matrix(std::vector<edge<T>> edges, std::vector<node<T>> nodes){
  // Initialize clear matrix
  for (auto& node : nodes) cells.emplace_back({})
  for (auto& row : cells)
    for (auto& line : nodes)
      row.emplace_back(-1);

  // Setting weights accordingly
  for (auto& edge : edges) set(edge);
};

template<class T>
bool matrix<T>::contains(const unsigned int i, const unsigned int j){
  if (i < 0 || i >= cells.size())    return false;
  if (j < 0 || j >= cells[i].size()) return false;
  return true;
}

template<class T>
void matrix<T>::set(edge<T> edge){
  if contains(edge.from(), edge.to()) cells[i][j] = edge.weight;
};