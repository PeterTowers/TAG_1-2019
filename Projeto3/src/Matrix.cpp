#include "../include/Matrix.hpp"

template<class T, class U>
Matrix<T,U>::Matrix(std::vector<T> leftGroup, std::vector<U> rightGroup, std::vector<Edge> edges)
  : left(leftGroup),
    right(rightGroup){
  // Initialize clear matrix
  for (int i = 0; i < leftGroup.size(); i++){
    cells.emplace_back(std::vector<int>());
    for (auto& line : rightGroup)
      cells[i].emplace_back(-1);
  }

  // Setting weights accordingly
  for (auto& edge : edges) set(edge);
};

template<class T, class U>
std::vector<std::vector<int>> Matrix<T,U>::rows(){ return cells; }

template<class T, class U>
bool Matrix<T,U>::contains(const unsigned int i, const unsigned int j){
  if (i < 0 || i >= left.size())  return false;
  if (j < 0 || j >= right.size()) return false;
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
void Matrix<T,U>::set(unsigned int a, unsigned int b, int weight){
  std::cout << "cells: (" << cells.size() << "," << cells[0].size() << ")" << std::endl;
  
  std::cout << "cells[" << a << "].size()" << cells[a].size() << std::endl;
  if (contains(a, b)) cells[a][b] = weight;
  std::cout << "setting edge: (" << a << "," << b << ") \t| "
            << (contains(a, b) ? "contained" : "not contained")
            << " within [(0, " << left.size() << "), (0, " << right.size() << ")]"
            << std::endl;
};


template<class T, class U>
unsigned int Matrix<T,U>::minimum(unsigned int index, bool columnwise){
  auto array = columnwise ? (*this)|index : (*this)[index];

  return array.empty() ? 0 : *std::min_element(array.begin(), array.end());
}


// Clones itself, except for the specified rows and columns
template<class T, class U>
Matrix<T,U> Matrix<T,U>::without(std::vector<unsigned int> rows, std::vector<unsigned int> columns){
    Matrix<T,U> result = {};

    return result;
}

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
    std::vector<Edge> edges = {};

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
    std::vector<Edge> edges = {};

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

  auto schools = left;   // left (schools)   | 50
  auto teachers = right; // right (teachers) | 100

  // assign each teacher to be free;
  std::vector<bool> free = {};
  for (auto& teacher : teachers) free.push_back(true);

  // assign school to be totally unsubscribed;
  std::vector<std::vector<unsigned int>> assignments = {};
  for (auto& school : schools) school.teachers.clear();

  // Checks if there is a free teacher
  auto findTeacher = [&](){
    for (int i = 0; i < teachers.size(); i++)
      if (free[i] && !teachers[i].get_schools().empty())
        return i;

    return -1;
  }

  // Get first teacher that meets requirements
  for (int teacherIndex = 0; teacherIndex > -1; teacherIndex = findTeacher()){
    auto& teacher = teachers[teacherIndex];
    
    // pj = first project on si’s list;
    auto preferences = teacher.get_schools();
    auto pref = schools[preferences[0]-1]; // FIXME: is 'id' always index + 1?

    // Provisionally assign si to pj; /* and to lk */
    auto& assignments = assignments[preferences[0]-1];
    assignments.push_back(teacherIndex);

    // Treat Exceptions:

    // 1. Over-Assignment
    if(assignments.size() > pref.getRequirements().size()){
      
      // Find worst assigned teacher
      auto worst = assignments.begin();
      for(auto a : assignments)
        if(teachers[*a].get_skills() < teachers[*worst].get_skills())
          indexOfWorst = a;
      
      // Break provisional assignment between sr and pj;
      assignments.erase(worst);

    //   t = worst teacher assigned to school;
    //   /* according toLjk*/
    //     break provisional assignment between sr and pj;
    //   } else if (lk is over-subscribed){
    //     sr = worst student assigned to lk;
    //     pt = project assigned sr;
    //     break provisional assignment between sr and pt;
    }
  }
  

  // while(some student si is free and si has a non-empty list){
  //   pj = first project on si’s list;
  //   lk = lecturer who offers pj; /*si applies to pj*/
  //   provisionally assign si to pj; /* and to lk*/

  //   if(pj is over-subscribed){
  //     sr = worst student assigned to pj;
  //   /* according to Ljk*/
  //     break provisional assignment between sr and pj;
  //   } else if (lk is over-subscribed){
  //     sr = worst student assigned to lk;
  //     pt = project assigned sr;
  //     break provisional assignment between sr and pt;
  //   }
    
  //   if (pj is full){
  //     sr= worst student assigned to pj;
  //     /* according to Ljk */
  //     for (each successor st of sr on Ljk)
  //       delete (st, pj);
  //     }
  //     if (lk is full){
  //       sr= worst student assigned to lk;

  //     for (each successor st of sr on Lk)
  //       for (each projectpu∈Pk∩At)
  //         delete (st, pu);
  //   }
  // }
    
  //   return{ (si, pj) ∈S×P : si is provisionally assigned to pj};
  // }



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

      std::cout << " : \t[ ";
      auto edges = (*this)[i];

      // Print edges within given row
      for (auto& edge : edges){
        std::cout << edge;
        // if (neighbot+1 == (*this).end()) std::cout << ", " << '\t';
        std::cout << ", ";
      }

      std::cout << " ] " << std::endl;
    }

    std::cout << std::endl;

    // Print right group
    for (auto& node : this->right){
      print(node);
      std::cout << " ";
    };
    std::cout << std::endl;
}


template <class T, class U>
void Matrix<T,U>::push(T row){
  this->left.push_back(row);

  cells.push_back({});
  auto newedges = cells[cells.size()-1];
  
  for (auto& node : this->right)
    newedges.push_back(-1);
}

template <class T, class U>
void Matrix<T,U>::push(U col){
  this->right.push_back(col);

  for (auto& row : this->cells) row.push_back(-1);
}


// FIXME: ANTIPATTERN WARNING
#include "../include/Teacher.hpp"
#include "../include/School.hpp"
template class Matrix<Teacher, School>;
template class Matrix<School, Teacher>;