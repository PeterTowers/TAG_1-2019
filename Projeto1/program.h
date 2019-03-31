#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _VERTEX_H
#define _VERTEX_H

int load(NETWORK* network, char* filename);
void print_vertex(VERTEX v);
void print_vertices(NETWORK n);
int cleanup(NETWORK* network);

#endif