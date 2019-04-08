#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "bklist.h"

#ifndef _BRON_KERBOSCH_H
#define _BRON_KERBOSCH_H

// A função bron_kerbosch() utiliza o algoritmo de Bron-Kerbosch com pivô listado acima para calcular e imprimir todos
// os cliques maximais do grafo.
void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x, NETWORK* network);

// Função para encontrar os cliques maximais fazendo a chamada inicial de bron_kerbosch()
int max_clique(NETWORK*);

#endif