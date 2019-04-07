#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "readgml.h"
#include "bronkerbosch.h"
#include "agglomeration.h"

int load(NETWORK* network, char* filename){
  FILE *fptr;
  FILE *tmp;
  char c;

  fptr = fopen(filename, "r");
  if (fptr == NULL ) {
      printf("Cannot open file.\n");
      return 0;                         // TODO: Mudar returns. Em C, return 0 indica sucesso - Pedro
  }
  if(read_network(network, fptr) != 0){
      printf("Could not read network");
      exit(77);
  }

  fclose(fptr);
  return 1;
};

int cleanup(NETWORK* network){
  free_network(network);
  return 1;
};

void print_vertex(VERTEX v){
  printf("[print_vertex] vertex: %i - degree: %i\n", v.id, v.degree);
  return;
};

void print_vertices(NETWORK network){
  if (network.nvertices <= 0)
    printf("[print_vertices] error: network has %i vertices", network.nvertices);
  for(int i = 0; i < network.nvertices; i++)
    print_vertex(network.vertex[i]);

    printf("\n[get_degrees] Greatest degree vertice: %i. Degree: %i\n", network.max_degree->id,
            network.max_degree->degree);
  return;
}

void question3(NETWORK* network){
  printf("[question 3] agglomeration coefficient for each vertex:\n");
  for(int i = 0; i < network->nvertices; i++)
    printf("\t %d: %f\n", network->vertex[i].id, agglomeration(network->vertex[i]));

}

void question4(NETWORK* network){
  printf("[question 4] average agglomeration coefficient for the graph: %f", avg_agglomeration(network));
}