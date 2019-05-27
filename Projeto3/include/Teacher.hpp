//
// Created by pedro on 25/05/19.
//
#pragma once

#include <vector>
#include "../include/School.hpp"
#include "./Node.hpp"

class Teacher : public Node {
private:
    int id, skills;
    std::vector<int> desiredSchools;

public:
    /*
     * Constructor & destructor
     */
    Teacher(int id, int skills, std::vector<int> desired): id(id), skills(skills), desiredSchools(desired) {};

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
    std::vector<int> get_schools() { return desiredSchools; };


};
