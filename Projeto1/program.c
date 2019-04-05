#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "readgml.h"

#define PRINT_FILE_INPUT 1

typedef struct BK_LIST{
    VERTEX vertex;

    struct BK_LIST* previous;
    struct BK_LIST* next;
} BK_LIST;

int max_clique(NETWORK* network);

int load(NETWORK* network, char* filename){
  FILE *fptr;
  FILE *tmp;
  char c;

  fptr = fopen(filename, "r");
  if (fptr == NULL ) {
      printf("Cannot open file.\n");
      return 0;                         // Mudar returns. Em C, return 0 indica sucesso - Pedro
  }

//  tmp = fptr;
//  if(PRINT_FILE_INPUT) while ((c = getc(tmp)) != EOF) putchar(c);
  
//    rewind(fptr);
  if(read_network(network, fptr) != 0){
      printf("Could not read network");
      exit(77);
  }

  int ok = max_clique(network);

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

void generate_list(NETWORK* network, struct BK_LIST* list) {
   struct BK_LIST *last, *current;

    list->previous = NULL;
    list->vertex = network->vertex[0];

    list->next = malloc(sizeof(BK_LIST));
    last = list;
    current = list->next;

    for(int i = 1; i < network->nvertices; i++) {
        last->next = current;

        current->previous = last;
        current->vertex=network->vertex[i];

        last = current;

        current->next = calloc(1, sizeof(BK_LIST));
        current = current->next;

    }

    return;
}

int bron_kerbosch(BK_LIST group_r, BK_LIST group_p, BK_LIST group_x) {
    return 0;
}

int max_clique(NETWORK* network) {
    BK_LIST* candidates = calloc(1, sizeof(BK_LIST));

    generate_list(network, candidates);

    BK_LIST* candidate3 = candidates->next;

    for(int i = 0; i < 2; i++)
        candidate3 = candidate3->next;

    printf("[max_clique] vertex: %i - degree %i\n\n", candidates->vertex.id, candidates->vertex.degree);
    if (candidates->next == NULL)
        printf("Could not generate bk_list");
    return 0;
}




