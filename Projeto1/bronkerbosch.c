#include "bronkerbosch.h"

#define TEST_LIST_FUNCTIONS

BK_LIST* new(VERTEX vertex){
  BK_LIST *head;
  head = malloc(sizeof(BK_LIST));
  head->vertex = vertex;
  head->previous = NULL;
  head->next = NULL;
  return head;
}

BK_LIST* clone(BK_LIST* list){
  if (list == NULL) return NULL;
  BK_LIST *head;

  head = new(list->vertex);
  head->next = clone(list->next);

  if (head->next != NULL) head->next->previous = head;

  return head;
}

BK_LIST* conjunction(BK_LIST* list, VERTEX vertex) {
  BK_LIST* copy = clone(list);
  BK_LIST* last = copy;

  while(last->next != NULL) last = last->next;
  last->next = new(vertex);
  last->next->previous = last;

  return copy;
}
// BK_LIST conjunction(BK_LIST, BK_LIST);


int contains(BK_LIST* list, VERTEX vertex){
  if (list == NULL) return 0;
  return (list->vertex.id == vertex.id) || contains(list->next, vertex);
}

BK_LIST* intersection(BK_LIST* list1, BK_LIST* list2) {
  if (list1 == NULL || list2 == NULL) return NULL;
  
  BK_LIST *head = NULL;
  VERTEX vertex = list1->vertex;

  if (contains(list2, list1->vertex)){
    head = new(vertex);
    head->next = intersection(list1->next, list2);
    if (head->next != NULL) head->next->previous = head;
  }
  else head = intersection(list1->next, list2);

  return head;
}

BK_LIST* disjunction(BK_LIST* list, VERTEX vertex) {
  if (list == NULL) return NULL;
  if (list->vertex.id == vertex.id) return disjunction(list->next, vertex);
  BK_LIST *head;
  
  head = new(list->vertex);
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

BK_LIST* bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x) {
    if ((group_p == NULL) && (group_x == NULL)) {
        printf("[bron_kerbosch] Maximal clique found between vertexes:\n");
        print_list(group_r);
        printf('\n');
    }

    while (group_p != NULL)

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
      VERTEX vertex = network->vertex[0];
      printf("---------------- TESTING CONJUNCTION\n");
      BK_LIST* con = conjunction(candidates, vertex);
      print_list(candidates);
      printf("%d\n", vertex.id);
      print_list(con);

      printf("---------------- TESTING DISJUNCTION\n");
      BK_LIST* dis = disjunction(candidates, vertex);
      print_list(candidates);
      printf("%d\n", vertex.id);
      print_list(dis);

      printf("---------------- TESTING CONTAINS\n");
      printf("%d\n", contains(con, vertex));
      printf("%d\n", contains(dis, vertex));

      printf("---------------- TESTING INTERSECTION\n");
      BK_LIST* inter = intersection(candidates, dis);
      BK_LIST* nil1 = intersection(NULL, candidates);
      BK_LIST* nil2 = intersection(candidates, NULL);
      print_list(inter);
      print_list(nil1);
      print_list(nil2);

      free(con);
      free(dis);
      free(inter);
      free(nil1);
      free(nil2);
    #endif

    return 0;
}

void destroy(BK_LIST* list) {
    BK_LIST *aux1, *aux2;

    aux1 = list;

    while (aux1->previous != NULL)
        aux1 = aux1->previous;

    while (aux2 != NULL) {
        aux2 = aux1->next;
        free(aux1);
    }
}