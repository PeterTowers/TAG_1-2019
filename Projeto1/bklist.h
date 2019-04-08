#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _BKLIST_H
#define _BKLIST_H

// Tipo BK_LIST: lista duplamente encadeada para armazenar os vértices de uma network
typedef struct bk_struct{
    VERTEX vertex;              // Armazena um vértice da network

    struct bk_struct* previous; // Ponteiro para o elemento anterior da lista
    struct bk_struct* next;     // Ponteiro para o próximo elemento
} BK_LIST;

// Função para gerar uma lista de um unico elemento com o vértice passado
BK_LIST* new(VERTEX);

// A função clone() clona uma lista para um outro endereço de memória
BK_LIST* clone(BK_LIST*);


// length() calcula o comprimento de uma lista
int length(BK_LIST*);

// conjunction() adiciona um vértice na última posição da lista
BK_LIST* conjunction(BK_LIST*, VERTEX);

// contains() retorna um "booleano" indicando se uma lista contém um elemento
int contains(BK_LIST*, VERTEX);

// Função para gerar uma lista contendo a interseção entre duas listas
BK_LIST* intersection(BK_LIST*, BK_LIST*);

// Função para remover um elemento de uma lista
BK_LIST* disjunction(BK_LIST*, VERTEX);

// Função para fazer uma união algébrica entre duas listas
BK_LIST* algebraic_union(BK_LIST*, BK_LIST*);

// Função para imprimir os indices dos vértices dentro de uma lista
void print_list(BK_LIST*);

// Função recursiva para criar uma lista de vértices a partir da network disponível
BK_LIST* generate_list(NETWORK*, BK_LIST*, int);

// Função para gerar uma lista de vértices vizinhos a um outro
BK_LIST* find_neighbours (NETWORK*, BK_LIST*, VERTEX, int);

// Função para encontrar o vértice de maior grau dentro de uma lista
VERTEX find_greatest_degree (BK_LIST*);

// Função para desalocar a memória utilizada por uma lista
void destroy(BK_LIST* list);

#endif