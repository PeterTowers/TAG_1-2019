#pragma once
#include <iostream>
#include "node.hpp"


// TODO: Implement class properly
template <class T> class edge {
  private:
    unsigned int source;
    unsigned int target;
    int weight;

    std::function<node<T>*(unsigned int)> getNode; // A closure that allows a node to acess a graph's nodes and return them

  public:
    // Public methods
    edge(node<T>* source, node<T>* target, int weight = 0, std::function<node<T>*(unsigned int)> getNode = [](unsigned int index){ return nullptr; }) : 
      source(source),
      target(target),
      weight(weight) {};
    ~edge();

    // These return the IDs of the objects
    unsigned int from();
    unsigned int to();

    // These return the actual node references
    node<T>* sourceNode(){ return getNode(from()); };
    node<T>* targetNode(){ return getNode(to()); };

    // These check for edge equality
    bool operator==(edge<T> rhs){
      return this.from() == rhs.from() && this.to() == rhs.to();
    };

    bool involves(unsigned int id);
    bool involves(node<T> node);
};