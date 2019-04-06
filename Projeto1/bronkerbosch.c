#include "bronkerbosch.h"

#define TEST_LIST_FUNCTIONS


BK_LIST conjunction(BK_LIST list, VERTEX vertex) {
  // TODO: Implement method
  return list;
}
// BK_LIST conjunction(BK_LIST, BK_LIST);


BK_LIST intersection(BK_LIST list1, BK_LIST list2) {
  // TODO: Implement method
  return list1;
}


BK_LIST disjunction(BK_LIST list, VERTEX vertex) {
  // TODO: Implement method
  return list;
}
// BK_LIST disjunction(BK_LIST, BK_LIST);




void print_list(const BK_LIST *list){
  BK_LIST* tracer = list;

  printf("[print_list] (");
  while(tracer != NULL){
    printf("%d", tracer->vertex.id);
    if (tracer->next != NULL) printf(", ");

    tracer = tracer->next;
  }
  printf(")\n");
}

void generate_list(NETWORK* network, BK_LIST* list) {
   struct BK_LIST *last, *current;

    list->previous = NULL;
    list->vertex = network->vertex[0];

    list->next = malloc(sizeof(BK_LIST));
    last = list;
    current = list->next;

    for(int i = 1; i < network->nvertices; i++) {
        last->next = current;

        current->previous = last;
        current->vertex=network->vertex[i];

        last = current;

        current->next = calloc(1, sizeof(BK_LIST));
        current = current->next;

    }

    return;
}


/**
 * BronKerbosch1(R, P, X):
 *     if P and X are both empty:
 *         report R as a maximal clique
 *     for each vertex v in P:
 *         BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
 *         P := P \ {v}
 *         X := X ⋃ {v}
 *
 */

int bron_kerbosch(BK_LIST group_r, BK_LIST group_p, BK_LIST group_x) {
    return 0;
}

int max_clique(NETWORK* network) {
    BK_LIST* candidates = calloc(1, sizeof(BK_LIST));

    generate_list(network, candidates);

    BK_LIST* candidate3 = candidates->next;

//    for(int i = 0; i < 1; i++)
//        candidate3 = candidate3->next;

    printf("[max_clique] vertex: %i - degree %i\n\n", candidate3->vertex.id, candidate3->vertex.degree);
    if (candidates->next == NULL)
        printf("Could not generate bk_list");


    #ifdef TEST_LIST_FUNCTIONS
      printf("---------------- TESTING CONJUNCTION\n");
      BK_LIST con = conjunction(*candidates, network->vertex[0]);
      print_list(candidates);
      printf("%d\n", network->vertex[0].id);
      print_list(&con);
      
      

      printf("---------------- TESTING INTERSECTION\n");

      printf("---------------- TESTING DISJUNCTION\n");
    #endif

    return 0;
}

