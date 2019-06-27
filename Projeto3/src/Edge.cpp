#include "../include/Edge.hpp"
#include "../include/Node.hpp"


// Edge::from: return the edge's source node index
unsigned int Edge::from(){ return source; };

// Edge::from: return the edge's target node index
unsigned int Edge::to(){ return target; };


// (Overload) Edge::from(index): return true if the edge's source node index matches the passed value
bool Edge::from(unsigned int index){ return source == index; };

// (Overload) Edge::from(index): return true if the edge's target node index matches the passed value
bool Edge::to(unsigned int index){ return target == index; };

// Edge::involves(index): return true if either of the edge's source or target node indices matches the passed value
bool Edge::involves(unsigned int id) {
  return (from() == id || to() == id);
}

// (Overload) Edge::involves(index): return true edge's source node index matches the passed node's id
bool Edge::involves(Node node) { return involves(node.get_id()); }

// Edge::getWeight: returns the edge's weight
int Edge::getWeight(){ return weight; }