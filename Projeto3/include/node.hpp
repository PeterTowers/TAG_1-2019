#pragma once
#include <iostream>

// TODO: Implement class properly
template <class T> class node {
  private:
    T* data;

  public:
    unsigned int id;

    // Public methods
    node(T* data, unsigned int id) : data(data), id(id) {};
    ~node(){ }; // FIXME: Should this call "data" destructor?

    T    get();
    void set(T data);

    T operator()(){ return get(); }
    void operator=(const T data){ set(data); }
};