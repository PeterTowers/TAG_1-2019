#pragma once
#include <iostream>

// TODO: Implement class properly
class Node {
  protected:
    int id;

  public:
  
    // Public methods
    Node(int id) : id(id){};
    ~Node() {};

    int get_id() { return id; };

    // Node operator()(){ return get(); }
    bool operator==(Node rhs){ return rhs.get_id() == get_id(); }
};