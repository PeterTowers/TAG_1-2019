/* course's class methods */

#include "../include/course.hpp"

// Constructor
course::course(unsigned int id, std::string name, unsigned int credits, std::function<void(course)> callback)
    : id(id),           // Sets values received to theirs respective variables
      name(name),
      credits(credits)
{
    callback(*this);
}

// Destructor
course::~course() { }

// Gets credits value from a course
int cost(course c) { return c.credits; }    // TODO: cleanup?