#include "../include/matrix.hpp"
#include "../include/course.hpp" // FIXME: This is an antipattern

template<class T>
matrix<T>::matrix(std::vector<node<T>> leftGroup, std::vector<node<T>> rightGroup, std::vector<edge<T>> edges){

  // Initialize clear matrix
  for (auto& node : leftGroup) cells.emplace_back(std::vector<int>());
  for (auto& row : cells)
    for (auto& line : rightGroup)
      row.emplace_back(-1);

  // Setting weights accordingly
  for (auto& edge : edges) set(edge);
};

template<class T>
std::vector<std::vector<int>> matrix<T>::rows(){ return cells; }

template<class T>
bool matrix<T>::contains(const unsigned int i, const unsigned int j){
  if (i < 0 || i >= cells.size())    return false;
  if (j < 0 || j >= cells[i].size()) return false;
  return true;
}

template<class T>
bool matrix<T>::empty(){
  return left.empty() || right.empty();
}

template<class T>
void matrix<T>::set(edge<T> edge){
  if (contains(edge.from(), edge.to())) cells[edge.from()][edge.to()] = edge.getWeight();
};

template<class T>
unsigned int matrix<T>::minimum(unsigned int index, bool columnwise){
  auto array = columnwise ? (*this)|index : (*this)[index];

  return array.empty() ? 0 : *std::min_element(array.begin(), array.end());
}


// TODO: Finish
// Clones itself, except for the specified rows and columns
template<class T>
matrix<T> matrix<T>::without(std::vector<unsigned int> rows, std::vector<unsigned int> columns){
    matrix<T> result = {};

    return result;
}

// TODO: Finish
template<class T>
matrix<T> matrix<T>::filter(std::function<bool(std::vector<int>)> predicate, bool bothDirections){
  if (bothDirections)
    return this->filter(predicate, false)
                .flipped()
                .filter(predicate, false)
                .flipped();

  auto left = this->left;
  auto cells = this->cells;

  auto wrapped_predicate = [=](auto it){ return predicate(cells[std::distance(left.begin(), it)]); };

  std::remove_if(left.begin(), left.end(), wrapped_predicate);
  std::remove_if(cells.begin(), cells.end(), predicate);

  std::vector<edge<T>> edges = {};

    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        edges.emplace_back(i, j, cells[i][j]);

  return matrix<T>(left, this->right, edges);
}

/* Returns a version of itself where every row and column is subtracted
  to the point where the minimum value is zero.
*/
template<class T>
matrix<T> matrix<T>::minimized(){
    matrix<T> result(*this);
    int min = 0;
    auto subtract_minimum = [=](int weight){ return weight - min; };

    // 1. Minimize matrix row-wise
    for (auto row : result.rows()){
        min = *std::min_element(row.begin(), row.end());
        std::transform(row.begin(), row.end(), row.begin(), subtract_minimum);
    }

    result = result.flipped();

    // 2. Minimize matrix column-wise
    for (auto row : result.rows()){
        min = *std::min_element(row.begin(), row.end());
        std::transform(row.begin(), row.end(), row.begin(), subtract_minimum);
    }

    return result = result.flipped();
}


template<class T>
matrix<T> matrix<T>::flipped(){
    std::vector<edge<T>> edges;

    // Create edges from inverted cells
    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        edges.emplace_back(j, i, cells[i][j]);

    // Create and return result matrix
    return matrix<T>(right, left, edges);
}


template<class T>
std::vector<edge<T>> matrix<T>::pairing(){
  std::vector<edge<T>> result = {};
  if (empty()) return result;

  // Filtering function, which detects independent zeroes
  auto nozeroes = [](std::vector<int> line){
    for(auto& item : line) if(item == 0) return false;
    return true;
  };

  // 1. De cada linha e coluna, subtrair seu elemento minimo
  matrix<T> min = this->minimized();

  // 2. Achar Zeros Independentes
  result = min.zeroes();

  // 3. Se N' = MM eses zeros foram encontrados: retornar os indices e parar
  for (auto& edge : min.filter(nozeroes).filter(nozeroes, true).pairing())
    result.push_back(edge);

  return result;
};



template <class T>
void matrix<T>::inspect(std::function<void(node<T>)> print) {

    // Print left group and edge costs
    for (int i = 0; i < left.size(); i++){
      auto& node = left[i];
      print(node);

      std::cout << " : [ ";
      auto edges = (*this)[i];

      // Print edges within given row
      for (auto& edge : edges){
        std::cout << edge;
        // if (neighbot+1 == (*this).end()) std::cout << ", " << '\t';
        std::cout << ", " << '\t';
      }

      std::cout << " ] " << std::endl;
    }

    // Print right group
    for (auto& node : right) print(node);
    std::cout << std::endl;
}


template class matrix<course>; // FIXME: This is an antipattern