#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "bklist.h"

#ifndef _BRON_KERBOSCH_H
#define _BRON_KERBOSCH_H

// TODO: Document method - bron_kerbosch
void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x, NETWORK* network);

// TODO: Document method - max_clique
int max_clique(NETWORK*);

#endif