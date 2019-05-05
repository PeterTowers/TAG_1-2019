#pragma once
#include <iostream>
#include <vector>
#include <functional>

class course
{
public:
    const unsigned int id;
    const unsigned int credits;
    const std::string name;

    course(unsigned int, std::string, unsigned int, std::function<void(course)> callback = [](course){});
    ~course();
};

