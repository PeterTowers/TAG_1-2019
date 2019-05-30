#include "../include/reader.hpp"

/** comment: Tells wether a given string is a comment or not
 *    Receives:
 *      - A string
 *    Returns:
 *      - true if the string is a comment, ie, starts with '#'
 */
bool comment(char c) { return c == '#'; }

// build: Parses an array of strings into a graph
void build(std::vector<std::string> stream, Graph* graph, Matrix<Teacher, School>* matrix) {
    // Check input
    if (stream.empty()) exit(-666); // TODO: correct this accordingly


    std::vector<Teacher> teachers;
    std::vector<School> schools;

    // Run through file
    for(auto line : stream) {
        // Eat comments
        if ( comment(line.front()) ) continue;

        // Define regexes for digits, teachers (professor) and schools ( if needed, it's here: regexSchool("^\\(E") )
        std::regex regexDigits("(\\d+)"), regexProfessor("P");

        // Store regex's matches
        std::smatch match;

        // Iterator to find multiple matches in a string
        std::string::const_iterator searchStart(line.cbegin());

        // Counts iterations to find where to place data
        int i = 0;

        // Stores the id and the number of skills a teacher has
        int id, skills;

        // Stores a teacher's desired schools or the number of skills required by a school
        std::vector<int> desired;

        // Iterates through a line in order to find all the digits it contains
        while ( std::regex_search(searchStart, line.cend(), match, regexDigits) ) {

            // If given line relates to a teacher, stores its data accordingly
            if (std::regex_search(line, regexProfessor)) {
                if (i == 0)                     // The first digit is the teacher's id
                    id = std::stoi(match[0]);
                else if (i == 1)                // The second, their number of skills
                    skills = std::stoi(match[0]);
                else                            // The others are their desired schools
                    desired.push_back(std::stoi(match[0]));
            }

            // If it's not related to a teacher, then, it's a school
            else {
                if (i == 0)                     // The first digit is the school's id
                    id = std::stoi(match[0]);
                else                            // The others are the number of skills required for each position
                    desired.push_back(std::stoi(match[0]));
            }

            // Make the changes needed to iterate through data and line
            i++;
            searchStart = match.suffix().first;
        }

        // If line relates to a teacher, store teacher's data in an object and add it to 'teachers' vector
        if (std::regex_search(line, regexProfessor)) {
            Teacher teacher(id, skills, desired);
            teachers.push_back(teacher);
        }
        // Else, stores accordingly
        else {
            School school(id, desired);
            schools.push_back(school);
        }
    }

    /* ~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*~=*
     * ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* GLORIOUS printf() DEBUGGING *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~
     * *=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~*=~
     */
    for (auto teacher : teachers) {
        if (graph != nullptr) graph->push(teacher);
        if (matrix != nullptr) matrix->push(teacher);

        std::cout << "Teacher's id: " << teacher.get_id();
        std::cout << "\tNumber of skills: " << teacher.get_skills() << std::endl;
        std::cout << "Desired school(s): ";
        for (auto school : teacher.get_schools())
            std::cout << school << ' ';

        std::cout << std::endl << std::endl;
    }

    for (auto school : schools) {
        if (graph != nullptr) graph->push(school);
        if (matrix != nullptr) matrix->push(school);

        std::cout << "School's id: " << school.get_id();
        std::cout << "\tAvailable positions: " << school.getRequirements().size() << std::endl;
        std::cout << "Number of desired skills for each position: ";
        for (auto number : school.getRequirements()) {
            std::cout << number << "; ";
        }

        std::cout << std::endl << std::endl;
    }
    /* ~*~*~*~*~*~*~* ALL HAIL ITS MIGHT! WE ONLY LIVE BECAUSE OF ITS BENEVOLENCE! *~*~*~*~*~*~*~ */



  // Construct Matrix
  // FIXME: This is not taking into account the schools requirements
  for(int teacher_index = 0; teacher_index < teachers.size(); teacher_index++){
    int priority = 0;
    for (auto desired : teachers[teacher_index].get_schools()) {
      std::cout << " | teacher_index: " << teacher_index
                << " | desired: "       << desired
                << " | priority: "      << priority
                << std::endl;
      matrix->set(teacher_index , desired - 1, priority);
      priority++;
    }
  }
}

// build overload: receives a filename, and call its homonim with the input properly split
void build(std::string filename, Graph* graph, Matrix<Teacher, School>* matrix) {
    // Loads file
    std::ifstream input(filename.c_str()); 

    // Catches bad input
    if (!input){
        std::cout << "[read] no input!";
        exit(-666); // TODO: correct this accordingly
//        return nullptr;
    }

    // Builds the stream
    std::string temp;
    std::vector<std::string> res;


    // Pushes each line into the output
    while(std::getline(input, temp)) res.push_back(std::string(temp.c_str()));

    // Passes output into homonim
    return build(res, graph, matrix);
}
