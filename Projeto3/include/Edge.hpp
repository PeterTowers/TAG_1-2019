#pragma once
#include <iostream>
#include <functional>
#include "Node.hpp"


// TODO: Implement comparison operators <, >
class Edge {
  private:
    unsigned int source;
    unsigned int target;
    int weight;

    std::function<Node*(unsigned int)> getNode; // A closure that allows a node to acess a graph's nodes and return them

  public:
    // Public methods
    Edge(unsigned int source, unsigned int target, int weight = 0, std::function<Node*(unsigned int)> getNode = [](unsigned int index){ return nullptr; })
      : source(source),
        target(target),
        weight(weight),
        getNode(getNode) {};
    ~Edge(){};

    // These return the IDs of the objects
    unsigned int from();
    unsigned int to();


    // These indicate whether an edge starts or ends at a particular index
    bool from(unsigned int);
    bool to(unsigned int);

    // These return the actual node references
    Node* sourceNode(){ return getNode(from()); };
    Node* targetNode(){ return getNode(to()); };

    // These check for edge equality
    bool operator==(Edge rhs){
      return this->from() == rhs.from() && this->to() == rhs.to();
    };

    bool involves(unsigned int id);

    int getWeight();
    bool involves(Node node);
};