#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _PROGRAM_H
#define _PROGRAM_H

// Função para abrir o arquivo karate.gml e criar o grafo a partir dele
int load(NETWORK*, char*);

// Função chamada para desalocar a memória utilizada pela network
int cleanup(NETWORK*);

// Função para imprimir o id e o grau do vértice passado
void print_vertex(VERTEX v);

// Função relativa ao objetivo 1 do projeto: imprimir cada vértice do grafo e seu respectivo grau
void question1(NETWORK);

// Função relativa ao objetivo 2 do projeto: encontrar e imprimir todos os cliques maximais
void question2(NETWORK*);

// Função para encontrar os cliques maximais fazendo a chamada inicial de bron_kerbosch()
int max_clique(NETWORK* network);

// Função relativa ao objetivo 3 do projeto: calcular e imprimir o coeficiente de aglomeração de cada vértice
void question3(NETWORK*);

// Função relativa ao objetivo 4 do projeto: calcular e imprimir o coeficiente médio de aglomeracao do grafo
void question4(NETWORK*);


#endif
