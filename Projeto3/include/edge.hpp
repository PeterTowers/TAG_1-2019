#pragma once
#include <iostream>


// TODO: Implement class properly
template <class T> class edge {
  private:
    T* source;
    T* target;

    unsigned int weight;

  public:
    edge(T* source, T* target) : 
      source(source)
      target(target) {};

    T* source(){ return source; };
    T* target(){ return target; };
}