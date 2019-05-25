#pragma once
#include <iostream>
#include "node.hpp"


// TODO: Implement class properly
template <class T> class edge {
  private:
    // `Private` props
    node<T>* source;
    node<T>* target;
    unsigned int weight;

  public:
    // Public methods
    edge(node<T>* source, node<T>* target, unsigned int weight = 0) : 
      source(source),
      target(target),
      weight(weight) {};
    ~edge();

    node<T> from();
    node<T> to();
    bool involves(unsigned int id);
    bool involves(node<T> node);
};