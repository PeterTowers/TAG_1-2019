//
// Created by pedro on 25/05/19.
//

#ifndef PROJETO_3_TEACHER_HPP
#define PROJETO_3_TEACHER_HPP

#include <vector>
#include "../include/School.hpp"

class Teacher {
private:
    int id, skills;
    std::vector<School> desiredSchools;

public:
    /*
     * Constructor & destructor
     */
    Teacher(int id, int skills, std::vector<School> desired): id(id), skills(skills), desiredSchools(desired) {};

    ~Teacher() {};

    /*
     * Method get_id returns the teacher's id
     */
    int get_id() { return id; };

    /*
     * Method get_skills returns how many skills the teacher has
     */
    int get_skills() { return skills; };

    /*
     * Method get_school returns the list of schools in which the teacher wants to work
     */
    std::vector<School> get_schools() { return desiredSchools; };


};

#endif //PROJETO_3_TEACHER_HPP
