#include <stdio.h>
#include <stdlib.h>

#include "network.h"

#ifndef _AGGLOMERATION_H
#define _AGGLOMERATION_H

// triangle_count: para um dado vertice, calcula o numero de triangulos, formado por ele e dois vizinhos
int triangle_count(VERTEX, NETWORK*);

// agglomeration: calcula o coeficiente de aglomeracao de um dado vertice
float agglomeration(NETWORK*, int);

// avg_agglomeration: calcula o coficiente medio de aglomeracao do grafo
float avg_agglomeration(NETWORK*);

#endif