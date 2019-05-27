#include "../include/edge.hpp"
#include "../include/course.hpp" // FIXME: This is an antipattern

template <class T>
unsigned int edge<T>::from(){ return source; };

template <class T>
unsigned int edge<T>::to(){ return target; };

template <class T>
bool edge<T>::from(unsigned int index){ return source == index; };

template <class T>
bool edge<T>::to(unsigned int index){ return target == index; };

template <class T>
bool edge<T>::involves(unsigned int id) {
  return (from() == id || to() == id);
}

template <class T>
bool edge<T>::involves(Node node) { return involves(node.id); }

template class edge<course>;