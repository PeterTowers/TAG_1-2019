#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "readgml.h"
#include "bronkerbosch.h"
#include "agglomeration.h"

// Função para abrir o arquivo karate.gml e criar o grafo a partir dele
int load(NETWORK* network, char* filename){
  FILE *fptr;

  fptr = fopen(filename, "r");
  if (fptr == NULL ) {
      printf("Nao foi possivel abrir o arquivo '.gml'.\n");
      return 1;
  }

  // Utiliza a função read_network() para construir o grafo com os dados contidos no arquivo 'data/karate.gml'
  if(read_network(network, fptr) != 0){
      printf("Nao foi possivel gerar a network.\n");
      exit(77);
  }

  fclose(fptr);
  return 0;
}

// Função chamada para desalocar a memória utilizada pela network
int cleanup(NETWORK* network){
  free_network(network);
  return 0;
}

// Função para imprimir o id e o grau do vértice passado
void print_vertex(VERTEX v){
  printf("Vertice de id: %2i - Grau: %2i\n", v.id, v.degree);
  return;
}

// Função relativa ao objetivo 1 do projeto: imprimir cada vértice do grafo e seu respectivo grau
void question1(NETWORK network){
  if (network.nvertices <= 0)
    printf("[question1] Erro na inicializacao da network: network contem %i vertices", network.nvertices);
  printf("Objetivo (1): imprimir cada vertice e seu respectivo grau.\n\n");
  for(int i = 0; i < network.nvertices; i++)
    print_vertex(network.vertex[i]);

  return;
}

// Função relativa ao objetivo 2 do projeto: encontrar e imprimir todos os cliques maximais
void question2(NETWORK* network) {
    printf("Objetivo (2): imprimir todos os cliques maximais.\n");
    if (max_clique(network) != 0)
        printf("Erro na função max_clique().");
}

// Função relativa ao objetivo 3 do projeto: calcular e imprimir o coeficiente de aglomeração de cada vértice
void question3(NETWORK* network){
  printf("Objetivo (3): coeficiente de aglomeracao de cada vértice\n\n");
  for(int i = 0; i < network->nvertices; i++)
    printf("\tVertice %2d - coeficiente: %f\n", network->vertex[i].id, agglomeration(network, i));

}

// Função relativa ao objetivo 4 do projeto: calcular e imprimir o coeficiente médio de aglomeracao do grafo
void question4(NETWORK* network){
  printf("\nObjetivo (4): coeficiente medio de aglomeracao do grafo: %f", avg_agglomeration(network));
}