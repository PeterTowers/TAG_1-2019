#include "../include/Edge.hpp"
#include "../include/Node.hpp" // FIXME: This is an antipattern

unsigned int Edge::from(){ return source; };

unsigned int Edge::to(){ return target; };

bool Edge::from(unsigned int index){ return source == index; };

bool Edge::to(unsigned int index){ return target == index; };

bool Edge::involves(unsigned int id) {
  return (from() == id || to() == id);
}

bool Edge::involves(Node node) { return involves(node.get_id()); }

template class Edge;