#pragma once
#include <iostream>
#include <functional>
#include "node.hpp"


// TODO: Implement comparison operators <, >
template <class T> class edge {
  private:
    unsigned int source;
    unsigned int target;
    int weight;

    std::function<node<T>*(unsigned int)> getNode; // A closure that allows a node to acess a graph's nodes and return them

  public:
    // Public methods
    edge(unsigned int source, unsigned int target, int weight = 0, std::function<node<T>*(unsigned int)> getNode = [](unsigned int index){ return nullptr; })
      : source(source),
        target(target),
        weight(weight),
        getNode(getNode) {};
    ~edge(){};

    // These return the IDs of the objects
    unsigned int from();
    unsigned int to();


    // These indicate whether an edge starts or ends at a particular index
    bool from(unsigned int);
    bool to(unsigned int);

    // These return the actual node references
    node<T>* sourceNode(){ return getNode(from()); };
    node<T>* targetNode(){ return getNode(to()); };

    // These check for edge equality
    bool operator==(edge<T> rhs){
      return this->from() == rhs.from() && this->to() == rhs.to();
    };

    bool involves(unsigned int id);
    bool involves(node<T> node);

    int getWeight();
};