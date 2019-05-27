//
// Created by pedro on 25/05/19.
//

#ifndef PROJETO_3_SCHOOL_HPP
#define PROJETO_3_SCHOOL_HPP

#include <vector>

class School {
private:
    int id;
    std::vector<int> skillRequirements;

public:
    /*
     * Constructor & destructor
     */
    School(int id, std::vector<int> requires): id(id), skillRequirements(requires) {};

    ~School() {};

    /*
     * Method get_id returns the school id
     */
    int get_id() { return id; };

    /*
     * Method get_requirements returns the school list of required number of skills for each vacancy
     */
    std::vector<int> getRequirements() { return skillRequirements; };
};

#endif //PROJETO_3_SCHOOL_HPP
