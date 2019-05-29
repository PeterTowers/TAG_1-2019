#include "../include/Matrix.hpp"

template<class T, class U>
Matrix<T,U>::Matrix(std::vector<T> leftGroup, std::vector<U> rightGroup, std::vector<Edge> edges)
  : left(leftGroup),
    right(rightGroup){
  // Initialize clear matrix
  for (auto& node : leftGroup) cells.emplace_back(std::vector<int>());
  for (auto& row : cells)
    for (auto& line : rightGroup)
      row.emplace_back(-1);

  // Setting weights accordingly
  for (auto& edge : edges) set(edge);
};

template<class T, class U>
std::vector<std::vector<int>> Matrix<T,U>::rows(){ return cells; }

template<class T, class U>
bool Matrix<T,U>::contains(const unsigned int i, const unsigned int j){
  if (i < 0 || i >= cells.size())    return false;
  if (j < 0 || j >= cells[i].size()) return false;
  return true;
}

template<class T, class U>
bool Matrix<T,U>::empty(){
  return left.empty() || right.empty();
}

template<class T, class U>
void Matrix<T,U>::set(Edge edge){
  std::cout << "setting edge: (" << edge.from() << "," << edge.to() << ") | "
            << (contains(edge.from(), edge.to()) ? "contained" : "not contained")
            << " within [(0" << left.size() << "), (0, " << right.size() << ")]"
            << std::endl;
  if (contains(edge.from(), edge.to())) cells[edge.from()][edge.to()] = edge.getWeight();
};


template<class T, class U>
unsigned int Matrix<T,U>::minimum(unsigned int index, bool columnwise){
  auto array = columnwise ? (*this)|index : (*this)[index];

  return array.empty() ? 0 : *std::min_element(array.begin(), array.end());
}


// TODO: Finish
// Clones itself, except for the specified rows and columns
template<class T, class U>
Matrix<T,U> Matrix<T,U>::without(std::vector<unsigned int> rows, std::vector<unsigned int> columns){
    Matrix<T,U> result = {};

    return result;
}

// TODO: Finish
template<class T, class U>
Matrix<T,U> Matrix<T,U>::filter(std::function<bool(std::vector<int>)> predicate, bool bothDirections){
  if (bothDirections)
    return this->filter(predicate, false)
                .flipped()
                .filter(predicate, false)
                .flipped();

  std::vector<unsigned int> toremove = {};


  // Specify which lines must be deleted
  int i = 0;
  for(auto& row : cells){
    if (predicate(row)) toremove.push_back(i);
    i++;
  }

  // Instaniate output
  std::vector<T> left(this->left);
  std::vector<std::vector<int>> cells(this->cells);

  // Delete elements
  for(auto index : toremove){
    left.erase(left.begin() + index);
    cells.erase(cells.begin() + index);
  }

  
  

  // myList.erase(
  //   std::remove_if(myList.begin(), myList.end(), IsMarkedToDelete),
  //   myList.end());

  std::vector<Edge> edges = {};
  for (int i = 0; i < cells.size(); i++)
    for (int j = 0; j < cells[i].size(); j++)
      edges.emplace_back(i, j, cells[i][j]);

  Matrix<T,U> result(left, this->right, edges);
  return result;
}

/* Returns a version of itself where every row and column is subtracted
  to the point where the minimum value is zero.
*/
template<class T, class U>
Matrix<T,U> Matrix<T,U>::minimized(bool bothDirections){
    Matrix<T,U> result(*this);
    int min = 0;
    auto subtract_minimum = [=](int weight){ return weight - min; };

    // 1. Minimize matrix row-wise
    for (auto row : result.rows()){
        min = *std::min_element(row.begin(), row.end());
        std::transform(row.begin(), row.end(), row.begin(), subtract_minimum);
    }

    // 2. If the requested minimization requires both directions, the algorithm is called once more.
    return bothDirections
      ? result.flipped().minimized(false).flipped()
      : result;
}


template<class T, class U>
std::vector<Edge> Matrix<T,U>::zeroes(){
    std::vector<Edge> edges;

    // Create edges from inverted cells
    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        if (cells[i][j] == 0)
          edges.emplace_back(i, j, cells[i][j]);

    // Create and return result matrix
    return edges;
}

template<class T, class U>
Matrix<U,T> Matrix<T,U>::flipped(){
    std::vector<Edge> edges;

    std::cout << "info: ";
    std::cout << "- length: " << right.size() << " | " << std::endl;
    std::cout << "- height: " << left.size() << " | " << std::endl;

    // Create edges from inverted cells
    for (int i = 0; i < cells.size(); i++)
      for (int j = 0; j < cells[i].size(); j++)
        edges.emplace_back(j, i, cells[i][j]);

    // Create and return result matrix



    
    // Initialize output
    std::vector<U> newright = { };
    std::vector<T> newleft = { };

    for (auto e : this->right) newright.push_back(e);
    for (auto e : this->left) newleft.push_back(e);


    std::cout << "info: ";
    std::cout << "- newlength: " << newright.size() << " | " << std::endl;
    std::cout << "- newheight: " << newleft.size()  << " | " << std::endl;

    Matrix<U,T> result(newright, newleft, edges);
    result.inspect();

    return result;
}


template<class T, class U>
std::vector<Edge> Matrix<T,U>::pairing(){
  std::vector<Edge> result = {};
  if (empty()) return result;

  // Filtering function, which detects independent zeroes
  auto nozeroes = [](std::vector<int> line){
    for(auto& item : line) if(item == 0) return false;
    return true;
  };

  // 1. De cada linha e coluna, subtrair seu elemento minimo
  Matrix<T,U> min = this->minimized();

  // 2. Achar Zeros Independentes
  result = min.zeroes();

  // 3. Se N' = MM eses zeros foram encontrados: retornar os indices e parar
  for (auto& edge : min.filter(nozeroes).filter(nozeroes, true).pairing())
    result.push_back(edge);

  return result;
};



template <class T, class U>
void Matrix<T,U>::inspect(std::function<void(Node)> print) {
    std::cout << "info: ";
    std::cout << "- length: " << right.size() << " | " << std::endl;
    std::cout << "- height: " << left.size() << " | " << std::endl;
    // Print left group and edge costs
    for (int i = 0; i < this->left.size(); i++){
      auto& node = left[i];
      print(node);

      std::cout << " : [ ";
      auto edges = (*this)[i];

      // Print edges within given row
      for (auto& edge : edges){
        std::cout << edge;
        // if (neighbot+1 == (*this).end()) std::cout << ", " << '\t';
        std::cout << ", ";
      }

      std::cout << " ] " << std::endl;
    }

    // Print right group
    for (auto& node : this->right) print(node);
    std::cout << std::endl;
}


template <class T, class U>
void Matrix<T,U>::push(T row){
  this->left.push_back(row);

  cells.push_back({});
  auto newedges = cells[cells.size()-1];
  
  for (auto node : this->right)
    newedges.push_back(-1);
}

template <class T, class U>
void Matrix<T,U>::push(U col){
  this->right.push_back(col);

  for (auto row : this->cells) row.push_back(-1);
}


// FIXME: ANTIPATTERN WARNING
#include "../include/Teacher.hpp"
#include "../include/School.hpp"
template class Matrix<Teacher, School>;
template class Matrix<School, Teacher>;