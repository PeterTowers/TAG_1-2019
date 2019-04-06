#include "bronkerbosch.h"

#define TEST_LIST_FUNCTIONS

BK_LIST* clone(BK_LIST* list){
  if (list == NULL) return NULL;
  BK_LIST *head;

  head = malloc(sizeof(BK_LIST));

  head->vertex = list->vertex;
  head->previous = NULL;
  head->next = clone(list->next);

  if (head->next != NULL) head->next->previous = head;

  return head;
}

BK_LIST* conjunction(BK_LIST* list, VERTEX vertex) {
  BK_LIST* copy = clone(list);
  BK_LIST* last = copy;

  while(last->next != NULL) last = last->next;
  last->next = malloc(sizeof(BK_LIST));
  
  last->next->previous = last;
  last->next->next = NULL;
  last->next->vertex = vertex;

  return copy;
}
// BK_LIST conjunction(BK_LIST, BK_LIST);


BK_LIST* intersection(BK_LIST* list1, BK_LIST* list2) {    // TODO: Implement method
   BK_LIST* intersected = malloc(sizeof(BK_LIST));
   BK_LIST* next1 = list1;
   BK_LIST* next2 = list2;

   while (next1 != NULL) {
       while (next2 != NULL) {
           if (next1->vertex.id == next2->vertex.id) intersected = conjunction(intersected, next1->vertex);
           next2 = next2->next;
       }
       next1 = next1->next;
   }

 return intersected;
}


BK_LIST* disjunction(BK_LIST* list, VERTEX vertex) {      // TODO: Implement method
  if (list == NULL) return NULL;
  if (list->vertex.id == vertex.id) return disjunction(list->next, vertex);
  BK_LIST *head;

  head = malloc(sizeof(BK_LIST));

  head->vertex = list->vertex;
  head->previous = NULL;
  head->next = disjunction(list->next, vertex);

  if (head->next != NULL) head->next->previous = head;

  return head;
}
// BK_LIST disjunction(BK_LIST, BK_LIST);




void print_list(BK_LIST *list){
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
   BK_LIST *last, *current;

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
        printf("Could not generate bk_list.\n");


    #ifdef TEST_LIST_FUNCTIONS
      printf("---------------- TESTING CONJUNCTION\n");
      BK_LIST* con = conjunction(candidates, network->vertex[0]);
      print_list(candidates);
      printf("%d\n", network->vertex[0].id);
      print_list(con);
      
      

      printf("---------------- TESTING INTERSECTION\n");
      BK_LIST* inter = conjunction(candidates, network->vertex[0]);
      print_list(inter);

      printf("---------------- TESTING DISJUNCTION\n");
      BK_LIST* dis = disjunction(candidates, network->vertex[0]);
      print_list(candidates);
      printf("%d\n", network->vertex[0].id);
      print_list(dis);

      free(con);
      free(inter);
      free(dis);
    #endif

    return 0;
}

