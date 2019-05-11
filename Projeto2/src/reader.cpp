#include "../include/reader.hpp"
#include <string>

// Split: divide uma string em substrings
// Function split() divides a string into substrings according to a set delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter)) tokens.push_back(token);
   return tokens;
}

// Treating commentary text
bool comment(std::string str) { return str.front() == '#'; }

// TODO: document function - prep
std::vector<std::string> prep(std::string input){
    std::vector<std::string> output;

    for (auto element : split(input, ' ')) if (comment(element)) break;
    for (auto element : split(input, ' ')) if (element > "")     output.push_back(element);

    return output;
}

// Function build() parses through an input STREAM and builds a digraph of courses
digraph<course>* build(std::vector<std::string> stream) {
    // Checks input
    if (stream.empty()) return nullptr;

    // Instantiates the digraph
    digraph<course> *output = new digraph<course>();

    // Runs through file
    for(auto line : stream) {
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

        std::cout << "[build] input: ";
        for(auto term : consumable)
            std::cout << "\""
                      << term
                      << "\" ";

        std::cout << std::endl;

        // Parse course ID
        unsigned int id = (unsigned int) std::stoul(consumable.front(), nullptr, 0);
        consumable.erase(consumable.begin());

        // Parse course Name
        std::string name = consumable.front();
        consumable.erase(consumable.begin());

        // Parse course Name
        unsigned int credits = (unsigned int) std::stoul(consumable.front(), nullptr, 0);
        consumable.erase(consumable.begin());
        
        // Create new node
        output->push(new course(id, name, credits));


        // Create edges
        for(auto prereq : consumable){
//            std::cout << "[build] prereq: "
//                  << '\''
//                  << prereq
//                  << '\''
//                  << std::endl;

            if (comment(consumable.front())) continue;
            else output->connect((unsigned int) std::stoul(prereq, nullptr, 0), id, [](course a){ return a.id; });
        }
    }
    return output;
}

// Function build() parses through an input FILE, builds a stream and passes it to the build() function above
digraph<course>* build(std::string filename) {
    std::ifstream input(filename.c_str());  // Loads file

    if (!input){                            // If there's an error with the file, returns a nullptr
        std::cout << "[read] no input!";
        return nullptr;
    }

    // Builds the stream
    std::string temp;
    std::vector<std::string> res;

    while(std::getline(input, temp)){
        // Debug Printings
        // #ifdef DEBUG_FILE_PRINTDATA
            std::cout << temp << std::endl;
        // #endif

        res.push_back(std::string(temp.c_str()));
    }

    return build(res);                      // Calls previous build() function passing built stream to it
}
