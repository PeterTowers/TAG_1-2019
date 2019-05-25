#include "../include/edge.hpp"

template <class T>
unsigned int edge<T>::from(){ return *source; };

template <class T>
unsigned int edge<T>::to(){ return *target; };

template <class T>
bool edge<T>::involves(unsigned int id) {
  return (from().id == id || to().id == id)
}

template <class T>
bool edge<T>::involves(node<T> node) { return involves(node.id) }
