#include "../include/reader.hpp"
#include <string>
#include <sstream>

// Split: divides a string into substrings, provided a given separator
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;    // Output container: array of parsed tokens
    std::string token;                  // Token buffer
    std::istringstream tokenStream(s);  // Input Stream

    // Grab tokens from the stream, passing the delimiter
    while (std::getline(tokenStream, token, delimiter)) tokens.push_back(token);
    return tokens;
}

/** comment: Tells wether a given string is a comment or not
 *    Receives:
 *      - A string
 *    Returns:
 *      - true if the string is a comment, ie, starts with '#'
 */
bool comment(std::string str) { return str.front() == '#'; }

/** prep: Prepare strings to be consumed by the parser
 *    Receives:
 *      - A string, representing a line in the input data file
 *    Returns:
 *      - An array of strings, comprised of the input string
 *        split into tokens, with comments ignored.
 */
std::vector<std::string> prep(std::string input){
    std::vector<std::string> output;

    // If token represents a comment, skip entire line
    for (auto element : split(input, ' ')) if (comment(element)) break;

    // If token represents data, push it into the array
    for (auto element : split(input, ' ')) if (element > "")     output.push_back(element);

    // Return the treated array of strings
    return output;
}

// build: Parses an array of strings into a graph
graph<course>* build(std::vector<std::string> stream) {

    // Check input
    if (stream.empty()) return nullptr;

    // Instantiate the graph
    graph<course> *output = new graph<course>();

    // Run through file
    for(auto line : stream) {
        
        // Create temporary buffer, which will be consumed
        std::vector<std::string> consumable(prep(line));

        // Eat comments
        if (comment(consumable.front())) continue;

        // Catch bad input
        if (consumable.size() < 3){
            std::cout << "[build] bad input: "
                      << line
                      << std::endl;
            continue;
        }

        // Parse (consume) 1st field: Course ID (integer)
        unsigned int id = (unsigned int) std::stoul(consumable.front(), nullptr, 0);
        consumable.erase(consumable.begin());

        // Parse (consume) 2nd field: Course Name (string)
        std::string name = consumable.front();
        consumable.erase(consumable.begin());

        // Parse (consume) 3rd field: Course Credits (integer)
        unsigned int credits = (unsigned int) std::stoul(consumable.front(), nullptr, 0);
        consumable.erase(consumable.begin());
        
        // Push parsed node into the graph
        output->push(new course(id, name, credits));


        /** Parse (consume) trailing parameters from the buffer (other course IDs),
          *   from which the edges of the graph are then constructed
          */
        for(auto prereq : consumable)
            if (comment(consumable.front())) continue;
            else output->connect((unsigned int) std::stoul(prereq, nullptr, 0), id);
    }
    return output;
}



// build overload: receives a filename, and call its homonim with the input properly split
graph<course>* build(std::string filename) {
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
