#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _VERTEX_H
#define _VERTEX_H


typedef struct BK_LIST{
    VERTEX vertex;

    struct BK_LIST* previous;
    struct BK_LIST* next;
} BK_LIST;

int max_clique(NETWORK* network);

int load(NETWORK* network, char* filename);
void print_vertex(VERTEX v);
void print_vertices(NETWORK n);
int cleanup(NETWORK* network);

#endif