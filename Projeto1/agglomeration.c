#include "network.h"

float agglomeration(VERTEX v){
  return 1.0;
}

float avg_agglomeration(NETWORK* network){
  VERTEX v;
  float acc = 0.0;

  for(int i = 0; i < network->nvertices; i++)
    acc += agglomeration(network->vertex[i]);

  return (acc / network->nvertices);
}