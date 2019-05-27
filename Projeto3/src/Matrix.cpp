#include "../include/Matrix.hpp"

template<class T>
Matrix<T>::Matrix(std::vector<Node> leftGroup, std::vector<Node> rightGroup, std::vector<Edge<T>> edges){
  // Initialize clear matrix
  for (auto& node : leftGroup) cells.emplace_back(std::vector<int>());
  for (auto& row : cells)
    for (auto& line : rightGroup)
      row.emplace_back(-1);

  // Setting weights accordingly
  for (auto& edge : edges) set(edge);
};

template<class T>
std::vector<std::vector<int>> Matrix<T>::rows(){ return cells; }

template<class T>
bool Matrix<T>::contains(const unsigned int i, const unsigned int j){
  if (i < 0 || i >= cells.size())    return false;
  if (j < 0 || j >= cells[i].size()) return false;
  return true;
}

template<class T>
bool Matrix<T>::empty(){
  return left.empty() || right.empty();
}

template<class T>
void Matrix<T>::set(Edge<T> edge){
  if (contains(edge.from(), edge.to())) cells[edge.from()][edge.to()] = edge.getWeight();
};


template<class T>
unsigned int Matrix<T>::minimum(unsigned int index, bool columnwise){
  auto array = columnwise ? (*this)|index : (*this)[index];

  return array.empty() ? 0 : *std::min_element(array.begin(), array.end());
}


// TODO: Finish
// Clones itself, except for the specified rows and columns
template<class T>
Matrix<T> Matrix<T>::without(std::vector<unsigned int> rows, std::vector<unsigned int> columns){
    Matrix<T> result = {};

    return result;
}

// TODO: Finish
template<class T>
Matrix<T> Matrix<T>::filter(std::function<bool(std::vector<int>)> predicate, bool bothDirections){
  if (bothDirections)
    return this->filter(predicate, false)
                .flipped()
                .filter(predicate, false)
                .flipped();

  auto left = this->left;
  auto cells = this->cells;

  int i = 0;
  auto wrapped_predicate = [=](auto it){ return predicate(cells[i]); };

  std::remove_if(left.begin(), left.end(), wrapped_predicate);
  std::remove_if(cells.begin(), cells.end(), predicate);

  std::vector<Edge<T>> edges = {};

    for (i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        edges.emplace_back(i, j, cells[i][j]);

  return Matrix<T>(left, this->right, edges);
}

/* Returns a version of itself where every row and column is subtracted
  to the point where the minimum value is zero.
*/
template<class T>
Matrix<T> Matrix<T>::minimized(){
    Matrix<T> result(*this);
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
std::vector<Edge<T>> Matrix<T>::zeroes(){
    std::vector<Edge<T>> edges;

    // Create edges from inverted cells
    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        if (cells[i][j] == 0)
          edges.emplace_back(i, j, cells[i][j]);

    // Create and return result matrix
    return edges;
}

template<class T>
Matrix<T> Matrix<T>::flipped(){
    std::vector<Edge<T>> edges;

    // Create edges from inverted cells
    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        edges.emplace_back(j, i, cells[i][j]);

    // Create and return result matrix
    return Matrix<T>(right, left, edges);
}


template<class T>
std::vector<Edge<T>> Matrix<T>::pairing(){
  std::vector<Edge<T>> result = {};
  if (empty()) return result;

  // Filtering function, which detects independent zeroes
  auto nozeroes = [](std::vector<int> line){
    for(auto& item : line) if(item == 0) return false;
    return true;
  };

  // 1. De cada linha e coluna, subtrair seu elemento minimo
  Matrix<T> min = this->minimized();

  // 2. Achar Zeros Independentes
  result = min.zeroes();

  // 3. Se N' = MM eses zeros foram encontrados: retornar os indices e parar
  for (auto& edge : min.filter(nozeroes).filter(nozeroes, true).pairing())
    result.push_back(edge);

  return result;
};



template <class T>
void Matrix<T>::inspect(std::function<void(Node)> print) {
    std::cout << "test";
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

