#include <stdio.h>
#include <stdlib.h>
#include "network.h"

#ifndef _BRON_KERBOSCH_H
#define _BRON_KERBOSCH_H

// TODO: Document data structure
typedef struct bk_struct{
    VERTEX vertex;

    struct bk_struct* previous;
    struct bk_struct* next;
} BK_LIST;

// TODO: Document method - cloee
BK_LIST* clone(BK_LIST* list);

// TODO: Document method - conjunction (union)
BK_LIST* conjunction(BK_LIST*, VERTEX);
// BK_LIST conjunction(BK_LIST, BK_LIST);

// TODO: Document method - intersection
BK_LIST* intersection(BK_LIST*, BK_LIST*);


// TODO: Document method - disjunction
BK_LIST* disjunction(BK_LIST*, VERTEX);
// BK_LIST disjunction(BK_LIST, BK_LIST);

// TODO: Document method - algebraic_union
BK_LIST* algebraic_union(BK_LIST* list1, BK_LIST* list2);

// TODO: Document method - generate_list
void generate_list(NETWORK*, BK_LIST*);

// TODO: Document method - find_neighbours
BK_LIST* find_neighbours (NETWORK network, VERTEX vertex);

// TODO: Document method - find_greatest_degree
BK_LIST* find_greatest_degree (BK_LIST* list);

// TODO: Document method - print_list
void print_list(BK_LIST*);

// TODO: Document method - bron_kerbosch
void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x);


// TODO: Document method - max_clique
int max_clique(NETWORK*);

// TODO: Document method - destroy
void destroy(BK_LIST* list);
#endif