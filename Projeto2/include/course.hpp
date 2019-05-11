#pragma once
#include <iostream>
#include <vector>
#include <functional>

// The course class saves data parsed from file '../data/materias.txt'
class course
{
public:
    const unsigned int id;      // Course's identification code ("Codigo")
    const unsigned int credits; // Course's credits ("Creditos")
    const std::string name;     // Course's name ("Nome da disciplina")

    // Class' constructor and destructor
    course(unsigned int, std::string, unsigned int, std::function<void(course)> callback = [](course){});
    ~course();
};

