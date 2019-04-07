#include "bklist.h"

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
    if (list == NULL) {
        BK_LIST* newList = new(vertex);
        return newList;
    }

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

BK_LIST* algebraic_union(BK_LIST* list1, BK_LIST* list2) {
    if (list1 == NULL)
        return list2;
    else if (list2 == NULL)
        return list1;
    else {
        BK_LIST *unionized = clone(list1);
        BK_LIST *aux = list2;


        while (aux != NULL) {
            if (contains(unionized, aux->vertex) != 0)
                conjunction(unionized, aux->vertex);

            aux = aux->next;
        }

        return unionized;
    }
}


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

BK_LIST* find_neighbours (NETWORK* network, BK_LIST* list, VERTEX vertex, int degree) {
    if ((degree == vertex.degree) || (vertex.degree == 0))
        return NULL;

    BK_LIST* neighbour = malloc(sizeof(BK_LIST));

    neighbour->previous = list;
    neighbour->vertex = network->vertex[vertex.edge[degree].target];
    neighbour->next = malloc(sizeof(BK_LIST));
    neighbour->next = find_neighbours(network, neighbour, vertex, ++degree);

    return neighbour;
}

VERTEX find_greatest_degree (BK_LIST* list) {
    if (list == NULL) {
        VERTEX errVertex;
        errVertex.degree = -1;

        return errVertex;
    }

    BK_LIST* aux = list->next;
    VERTEX max = list->vertex;

    while (aux != NULL) {
        if (aux->vertex.degree > max.degree) {
            max = aux->vertex;
        }
        aux = aux->next;
    }

    return max;
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