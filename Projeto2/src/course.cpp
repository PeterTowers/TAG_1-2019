#include "../include/course.hpp"


course::course(unsigned int id, std::string name, unsigned int credits, std::function<void(course)> callback)
    : id(id),
      name(name),
      credits(credits)
{
    callback(*this);
}

course::~course()
{
  
}

int cost(course c) { return c.credits; }