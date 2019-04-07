#include "network.h"

#include "bklist.h"

int length(BK_LIST* list){
  return list == NULL
    ? 0
    : 1 + length(list->next);
}

int triangle_count(VERTEX pivot, BK_LIST* neighbors){
  
};

float agglomeration(NETWORK* network, int index){
  VERTEX pivot = network->vertex[index];
  BK_LIST* neighbors = find_neighbours(network, NULL, pivot, 0);

  float t = (float) triangle_count(pivot, neighbors);

  destroy(neighbors);
  return (2.0 * t) / (pivot.degree * (pivot.degree - 1));
}

float avg_agglomeration(NETWORK* network){
  VERTEX v;
  float acc = 0.0;

  for(int i = 0; i < network->nvertices; i++)
    acc += agglomeration(network, i);

  return (acc / network->nvertices);
}