#include "../include/node.hpp"

template <class T>
T node<T>::get(){ return *data; };

template <class T>
void node<T>::set(T data){ *(this.data) = data; };