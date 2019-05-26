#include "../include/node.hpp"
#include "../include/course.hpp" // FIXME: This is an antipattern

template <class T>
T node<T>::get(){ return *data; };

template <class T>
void node<T>::set(T input){
  delete data;
  data = new T(input);
};

template class node<course>; // FIXME: This is an antipattern