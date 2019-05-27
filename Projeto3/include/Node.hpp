#pragma once
#include <iostream>

// TODO: Implement class properly
class Node {
  private:
    unsigned int id;

  public:
  
    // Public methods
    Node(unsigned int id);
    ~Node();

    Node get();
    void set(Node data);

    // Node operator()(){ return get(); }
    bool operator==(Node rhs){ return rhs.id == id; }
};