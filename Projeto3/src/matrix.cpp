#include "../include/matrix.hpp"

template<class T>
matrix<T>::matrix(std::vector<Edge<T>> edges, std::vector<Node> nodes){
  // Initialize clear matrix
  for (auto& node : nodes) cells.emplace_back(std::vector<int>());
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
void matrix<T>::set(Edge<T> edge){
  if (contains(edge.from(), edge.to())) cells[edge.from()][edge.to()] = edge.weight;
};