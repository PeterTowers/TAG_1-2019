#include "../include/Edge.hpp"
#include "../include/Node.hpp" // FIXME: This is an antipattern

template <class T>
unsigned int Edge<T>::from(){ return source; };

template <class T>
unsigned int Edge<T>::to(){ return target; };

template <class T>
bool Edge<T>::from(unsigned int index){ return source == index; };

template <class T>
bool Edge<T>::to(unsigned int index){ return target == index; };

template <class T>
bool Edge<T>::involves(unsigned int id) {
  return (from() == id || to() == id);
}

template <class T>
bool Edge<T>::involves(Node node) { return involves(node.get_id()); }

template class Edge<Node>;