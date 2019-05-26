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

    // Run through file
    for(auto line : stream) {
        // Eat comments
        if ( comment(line.front()) ) continue;

        std::regex exp("(\\d+)"), exp2("P");
        std::smatch match;

        std::string::const_iterator searchStart(line.cbegin());

        int i = 0;
        int id, skills;
        std::vector<int> desiredSchools;

        while ( std::regex_search(searchStart, line.cend(), match, exp) ) {
            if (std::regex_match(line, exp2)) {
                if (i == 0)
                    id = std::stoi(match[0]);
                else if (i == 1)
                    skills = std::stoi(match[0]);
                else
                    desiredSchools.push_back(std::stoi(match[0]));
            }
            else
                std::cout << ( searchStart == line.cbegin() ? "" : " ") << match[0];

            i++;
            searchStart = match.suffix().first;
        }
        std::cout << std::endl;
        if (std::regex_match(line, exp2)) {
            Teacher teacher(id, skills, desiredSchools);
            teachers.push_back(teacher);
        }
    }

    for (auto teacher : teachers) {
        std::cout << "Teacher's id: " << teacher.get_id();
        std::cout << "\tNumber of skills: " << teacher.get_skills() << std::endl;
        std::cout << "Desired school(s): ";
        for (auto school : teacher.get_schools())
            std::cout << school << ' ';

        std::cout << std::endl;
    }

}

// build overload: receives a filename, and call its homonim with the input properly split
void build(std::string filename) {
    // Loads file
    std::ifstream input(filename.c_str()); 

    // Catches bad input
    if (!input){
        std::cout << "[read] no input!";
        return nullptr;
    }

    // Builds the stream
    std::string temp;
    std::vector<std::string> res;


    // Pushes each line into the output
    while(std::getline(input, temp)) res.push_back(std::string(temp.c_str()));

    // Passes output into homonim
    return build(res);
}
