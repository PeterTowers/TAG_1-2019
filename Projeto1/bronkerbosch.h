#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _BRON_KERBOSCH_H
#define _BRON_KERBOSCH_H

// TODO: Document data structure
typedef struct BK_LIST{
    VERTEX vertex;

    struct BK_LIST* previous;
    struct BK_LIST* next;
} BK_LIST;

// TODO: Document method - conjunction (union)
BK_LIST conjunction(BK_LIST, VERTEX);
// BK_LIST conjunction(BK_LIST, BK_LIST);

// TODO: Document method - intersection
BK_LIST intersection(BK_LIST, BK_LIST);


// TODO: Document method - disjunction
BK_LIST disjunction(BK_LIST, VERTEX);
// BK_LIST disjunction(BK_LIST, BK_LIST);


// TODO: Document method - generate_list
void generate_list(NETWORK*, BK_LIST*);


// TODO: Document method - print_list
void print_list(const BK_LIST*);

// TODO: Document method - bron_kerbosch
int bron_kerbosch(BK_LIST, BK_LIST, BK_LIST);


// TODO: Document method - max_clique
int max_clique(NETWORK*);

#endif