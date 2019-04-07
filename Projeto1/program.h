#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _PROGRAM_H
#define _PROGRAM_H

// TODO: Document function signature - max_clique
int max_clique(NETWORK* network);

// TODO: Document function signature - load
int load(NETWORK* network, char* filename);

// TODO: Document function signature - print_vertex
void print_vertex(VERTEX v);

// TODO: Document function signature - print_vertices
void print_vertices(NETWORK n);

// TODO: Document function signature - cleanup
int cleanup(NETWORK* network);


#endif
