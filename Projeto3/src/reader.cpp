#include "../include/reader.hpp"

/** comment: Tells wether a given string is a comment or not
 *    Receives:
 *      - A string
 *    Returns:
 *      - true if the string is a comment, ie, starts with '#'
 */
bool comment(char c) { return c == '#'; }

// build: Parses an array of strings into a graph
void build(std::vector<std::string> stream) {

    // Check input
    if (stream.empty()) exit(-666); // TODO: correct this accordingly

    // TODO: Instantiate return type
//    graph<course> *output = new graph<course>();

    std::vector<Teacher> teachers;
    std::vector<School> schools;

    // Run through file
    for(auto line : stream) {
        // Eat comments
        if ( comment(line.front()) ) continue;

        // Define regexes for digits, teachers (professor) and schools
        std::regex regexDigits("(\\d+)"), regexProfessor("P"), regexSchool("^\\(E");

        // Store regex's matches
        std::smatch match;

        // Iterator to find multiple matches in a string
        std::string::const_iterator searchStart(line.cbegin());

        // Counts iterations to find where to place data
        int i = 0;

        // Stores the id and the number of skills a teacher have or a schoool desires
        int id, skills;

        // Stores a teacher's desired schools or the number of skills required by a school
        std::vector<int> desired;

        while ( std::regex_search(searchStart, line.cend(), match, regexDigits) ) {
            if (std::regex_search(line, regexProfessor)) {
                if (i == 0)
                    id = std::stoi(match[0]);
                else if (i == 1)
                    skills = std::stoi(match[0]);
                else
                    desired.push_back(std::stoi(match[0]));
            }
            else {
                if (i == 0)
                    id = std::stoi(match[0]);
                else
                    desired.push_back(std::stoi(match[0]));
            }
            i++;
            searchStart = match.suffix().first;
        }
        if (std::regex_search(line, regexProfessor)) {
            Teacher teacher(id, skills, desired);
            teachers.push_back(teacher);
        }
        else {
            School school(id, desired);
            schools.push_back(school);
        }
    }

    for (auto teacher : teachers) {
        std::cout << "Teacher's id: " << teacher.get_id();
        std::cout << "\tNumber of skills: " << teacher.get_skills() << std::endl;
        std::cout << "Desired school(s): ";
        for (auto school : teacher.get_schools())
            std::cout << school << ' ';

        std::cout << std::endl << std::endl;
    }

    for (auto school : schools) {
        std::cout << "School's id: " << school.get_id();
        std::cout << "\tAvailable positions: " << school.getRequirements().size() << std::endl;
        std::cout << "Number of desired skills for each position: ";
        for (auto number : school.getRequirements()) {
            std::cout << number << "; ";
        }

        std::cout << std::endl << std::endl;
    }

}

// build overload: receives a filename, and call its homonim with the input properly split
void build(std::string filename) {
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
    build(res);
}
