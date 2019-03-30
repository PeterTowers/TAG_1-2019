#include <stdio.h>
#include <stdlib.h>
#include "program.h"

void print_vertex(VERTEX v){
  printf("vértice: %i - grau: %i", v.id, v.degree);
  return;
};

void print_vertices(NETWORK network){
  for(int i = 0; i < network.nvertices; i++)
    print_vertex(network.vertex[i]);
  return;
};