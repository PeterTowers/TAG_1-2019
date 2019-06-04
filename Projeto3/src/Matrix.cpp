#include "../include/Matrix.hpp"

#define PRINT_MISSING_REQUIREMENTS

// Contructor method
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
}

// Getter function for matrix's rows
template<class T, class U>
std::vector<std::vector<int>> Matrix<T,U>::rows(){ return cells; }

// Indicates whether the passed indices are within the matrix's range
template<class T, class U>
bool Matrix<T,U>::contains(const unsigned int i, const unsigned int j){
    if (i < 0 || i >= left.size())  return false;
    if (j < 0 || j >= right.size()) return false;
    return true;
}

// Indicates whether the matrix's left or right group are empty
template<class T, class U>
bool Matrix<T,U>::empty(){
    return left.empty() || right.empty();
}

// Sets the weight of an edge
template<class T, class U>
void Matrix<T,U>::set(Edge edge){

    // If edge indices are within the matrix range, we set that cell to the give weight value
    if (contains(edge.from(), edge.to())) cells[edge.from()][edge.to()] = edge.getWeight();
};

// (Overload) Sets the weight of an edge, given two indices and a weight value explicitly
template<class T, class U>
void Matrix<T,U>::set(unsigned int a, unsigned int b, int weight){
  
  // If edge indices are within the matrix range, we set that cell to the give weight value
    if (contains(a, b)) cells[a][b] = weight;
};

/* Returns the minimum value within a line, unless 'flipped' is set to true, in which case it returns the minimum value
 * within column
 */
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

// Returns zero-weighed edges
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

// Calculates the optimal graph pairing and returns a vector of edges
template<class T, class U>
std::vector<Edge> Matrix<T,U>::pairing() {
    // Create a vector of edges to save and return the result
    std::vector<Edge> result = {};

    // Assign schools and teachers from a given matrix to a respective data structure in this scope
    auto schools = right;   // left (schools)   | 50
    auto teachers = left;   // right (teachers) | 100

    std::vector<bool> free = {};                        // Create a vector to represent if a teacher is already paired
    std::vector<std::vector<int>> teacherDesiredSchools;    // Holds each teacher preference list
    std::vector<unsigned int> rank;                         // Holds how the teacher ranked the current school in his
                                                            // preference list

    // Initialization of above vectors
    for (int i = 0; i < teachers.size(); i++) {
        free.push_back(true);                                       // Each teacher is assigned as free
        teacherDesiredSchools.push_back(teachers[i].get_schools()); // Each teacher have a copy of its preference list
        rank.push_back(0);                                          // Each teacher's index is set to 0
    }

    // Create a vector that holds the id of the teacher assigned to each of the school's vacancy and clear the data
    // structure to guarantee it is free of junk, so that all schools have its vacancies
    std::vector<std::vector<int>> assignments;

    // Sets the size of the array preemptively to avoid out of bounds access
    assignments.resize(schools.size());

    for (int i = 0; i < schools.size(); i++) {
        // Clear data structure to avoid junk stored in memory
        schools[i].clear_teachers();

        // Sets each element of the array as 0 so to indicate it as empty
        for (int j = 0; j < schools[i].get_requirements().size(); j++)
            assignments[i].push_back(-1);
    }

    // Checks if there's a free teacher and return its index on the array
    auto find_teacher = [&]() {
        for (int i = 0; i < teachers.size(); i++)
            if (free[i] && !teacherDesiredSchools[i].empty())
                return i;

        return -1;
    };

    // Iterates through all the available teachers
    for (int teacherIndex = 0; teacherIndex > -1; teacherIndex = find_teacher()) {
        // Get first teacher that meets requirements
        auto& teacher = teachers[teacherIndex];

        // Get the school id from a teacher's given list of preferred schools according to the rank index
        unsigned int schoolId = teacherDesiredSchools[teacherIndex][rank[teacherIndex]];

        // Assign the school to an object, since its index is always (id - 1)
        auto preferredSchool = schools[schoolId - 1];


        auto& assignment = assignments[schoolId - 1];   // Variable that references a given school's vacancies
        int assignmentIndex = -1;                       // Variable to hold an index for the variable above

        // Iterates through available vacancies of a given school
        for (int i = 0; i < preferredSchool.get_requirements().size(); i++) {

            // If the teacher has the skills necessary for a vacancy
            if (teacher.get_skills() >= preferredSchool.get_requirements()[i] ) {
                assignmentIndex = i;    // Save the given index

                // If there's a vacancy in school, the teacher can have it
                if (assignment[assignmentIndex] == -1) {
                    assignment[assignmentIndex] = teacherIndex;
                    free[teacherIndex] = false;

                    break;  // Exits loop
                }

                // Else, if the teacher ranked this school better than the teacher currently assigned to it
                else if (rank[teacherIndex] < rank[assignment[assignmentIndex]]) {
                    free[assignment[assignmentIndex]] = true;   // Free assigned teacher. No need to remove this school
                                                                // from his list yet, because he can run for another
                                                                // vacancy

                    // Assign teacher to this school and sets him as
                    // not free
                    assignment[assignmentIndex] = teacherIndex;
                    free[teacherIndex] = false;

                    break;  // Exits loop
                }

                /*
                 * Else, if both teachers ranked this school equally AND current teacher has lower skills than the
                 * teacher that's currently assigned to this school
                */
                else if (rank[teacherIndex] == rank[assignment[assignmentIndex]] &&
                            teacher.get_skills() < teachers[assignment[assignmentIndex]].get_skills()) {
                    /*
                     * Free assigned teacher. Again, no need to remove this school from his list yet. This is done so we
                     * don't waste the currently assigned teacher's skills to a school that needs less skills.
                    */
                    free[assignment[assignmentIndex]] = true;

                    // Assign teacher to this school and sets him as
                    // not free
                    assignment[assignmentIndex] = teacherIndex;
                    free[teacherIndex] = false;

                    break;  // Exits loop
                }
            }
        }

        // If 'assignmentIndex' didn't change in the loop above, the teacher isn't suitable for this school,
        // or, if he is suitable but there's no vacancy for him
        if (assignmentIndex == -1 || free[teacherIndex]) {
            // Remove the school from teacher's preference list
            teacherDesiredSchools[teacherIndex].erase(teacherDesiredSchools[teacherIndex].begin());

            rank[teacherIndex]++; // Updates their rank value increasing it by 1
        }

    }

    // // Fixing schools with no teachers
    // for (unsigned int schoolIndex = 0; schoolIndex < assignments.size(); schoolIndex++){
    // // for(auto& assignment : assignments){
    //   auto& assignment = assignments[schoolIndex];
    //   auto& school = schools[schoolIndex];
    //   for(auto& allocation : assignment) if (allocation < 0) {
    //     for(int i = 0; i < free.size(); i++)
    //       if (free[i]){  
    //         std::cout << "Fixing missing requirement | S" << schoolIndex << " -> P" << i << std::endl;
    //         // assignment.push_back(i);
    //         free[i] = false;
    //       }
    //   }
    // }

    // For each resulting assignment list (school)
    for (int schoolIndex = 0; schoolIndex < assignments.size(); schoolIndex++){

      std::cout << "Array with "  << assignments.at(schoolIndex).size() << " positions\n";
      
      // For each assigned teacher
      for (int teacherIndexPosition = 0;  teacherIndexPosition < assignments.at(schoolIndex).size(); teacherIndexPosition++)
        if (assignments.at(schoolIndex).at(teacherIndexPosition) < 0) {

          // If there is a free teacher
          for(int i = 0; i < free.size(); i++) if (free.at(i)){

              #ifdef PRINT_MISSING_REQUIREMENTS
              std::cout << "Fixing missing requirement | S"
                        << schoolIndex
                        << " -> P"
                        << i
                        << std::endl;
              #endif // PRINT_MISSING_REQUIREMENTS

              assignments.at(schoolIndex).at(teacherIndexPosition) = i;
              
              free.at(i) = false;
              break;
            }
      }
    }



    // Constructing result
    for (int i = 0; i < assignments.size(); i++)
        for (int j = 0; j < assignments[i].size(); j++) {
            if (assignments[i][j] == -1)
                result.emplace_back(schools[i].get_id(), 0);
            else
                result.emplace_back(schools[i].get_id(), teachers[assignments[i][j]].get_id());
        }

    return result;
}

// Prints data in human-readable format
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

// Push a new row
template <class T, class U>
void Matrix<T,U>::push(T row){
    // Insert a new node at the end of the left partition (new source)
    this->left.push_back(row);

    
    // Insert a new edge array at the end of the 'cells' array of arrays, matching the new source element
    cells.push_back({});
    auto newedges = cells[cells.size()-1];
    for (auto& node : this->right)
        newedges.push_back(-1);
}

// Push a new column into a matrix
template <class T, class U>
void Matrix<T,U>::push(U col){
    // Insert a new node at the end of the right partition (new target)
    this->right.push_back(col);

    // Insert a new element at the end of each row, matching the new target element;
    for (auto& row : this->cells) row.push_back(-1);
}

#include "../include/Teacher.hpp"
#include "../include/School.hpp"
template class Matrix<Teacher, School>;