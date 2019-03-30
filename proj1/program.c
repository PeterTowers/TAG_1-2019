#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "readgml.h"

#define PRINT_FILE_INPUT 1

int load(NETWORK* network, char* filename){
  FILE *fptr;
  FILE *tmp;
  char c;

  fptr = fopen(filename, "r");
  if (fptr == NULL ) {
      printf("Cannot open file");
      return 0;
  }

//  tmp = fptr;
//  if(PRINT_FILE_INPUT) while ((c = getc(tmp)) != EOF) putchar(c);
  
//    rewind(fptr);
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
  return;
};