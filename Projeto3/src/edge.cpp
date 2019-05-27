#include "../include/edge.hpp"
#include "../include/course.hpp" // FIXME: This is an antipattern

template <class T>
unsigned int Edge::from(){ return source; };

template <class T>
unsigned int Edge::to(){ return target; };

template <class T>
bool Edge::from(unsigned int index){ return source == index; };

template <class T>
bool Edge::to(unsigned int index){ return target == index; };

template <class T>
bool Edge::involves(unsigned int id) {
  return (from() == id || to() == id);
}

template <class T>
bool Edge::involves(node<T> node) { return involves(node.id); }

template <class T>
int Edge::getWeight() { return weight; };

template class edge<course>;