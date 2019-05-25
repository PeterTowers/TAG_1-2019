#include "../include/edge.hpp"

template <class T>
node<T> edge<T>::from(){ return *source; };

template <class T>
node<T> edge<T>::to(){ return *target; };

template <class T>
bool involves(unsigned int id) {
  return (from().id == id || to().id == id)
}

template <class T>
bool involves(node<T> node) { return involves(node.id) }
