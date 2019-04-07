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

    int aux = vertex.edge[degree].target;
    BK_LIST* neighbour = malloc(sizeof(BK_LIST));

    neighbour->previous = list;
    neighbour->vertex = network->vertex[aux];
    neighbour->next = malloc(sizeof(BK_LIST));
    neighbour->next = find_neighbours(network, neighbour, vertex, ++degree);

    return neighbour;
}

BK_LIST* find_greatest_degree (BK_LIST* list) {
    BK_LIST* max = list;
    BK_LIST* aux = list;

    if (list == NULL)
        return NULL;

    while (aux != NULL) {
        if (aux->vertex.degree > max->vertex.degree) {
            max = aux;
        }
        aux = aux->next;
    }

    return max;
}


/**
 * BronKerbosch2(R,P,X):
 *     if P and X are both empty:
 *         report R as a maximal clique
 *     choose a pivot vertex u in P ⋃ X
 *     for each vertex v in P \ N(u):
 *         BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
 *         P := P \ {v}
 *         X := X ⋃ {v}
 *
 */

//void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x) {
//    if ((group_p == NULL) && (group_x == NULL)) {
//        printf("[bron_kerbosch] Maximal clique found between vertexes:\n");
//        print_list(group_r);
//        printf('\n');
//
//
//    }
//
//    BK_LIST* pivot = find_greatest_degree()
//
//    while (group_p != NULL) {
//
//    };
//
//
//}

int max_clique(NETWORK* network) {
    BK_LIST* candidates = calloc(1, sizeof(BK_LIST));

    generate_list(network, candidates);

    BK_LIST* candidate3 = candidates->next;

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

        printf("---------------- TESTING ALG_UNION\n");

        printf("---------------- TESTING FIND_NEIGHBOURS\n");
        BK_LIST* aux = clone(candidates);
        BK_LIST* aux1 = aux->next;
        BK_LIST* aux2 = aux1->next;

        aux->next = malloc(sizeof(BK_LIST));
        aux1->next = malloc(sizeof(BK_LIST));
        aux2->next = malloc(sizeof(BK_LIST));

        aux->next = find_neighbours(network,aux, aux->vertex, 0);
        printf("aux->vertex.id: %i\n", aux->vertex.id);

        aux1->next = find_neighbours(network,aux1, aux1->vertex, 0);
        printf("aux1->vertex.id: %i\n", aux1->vertex.id);

        aux2->next = find_neighbours(network,aux2, aux2->vertex, 0);
        printf("aux2->vertex.id: %i\n", aux2->vertex.id);

        printf("\nNeighbours of vertex %i:\n", aux->vertex.id);
        print_list(aux);

        printf("\nNeighbours of vertex %i:\n", aux1->vertex.id);
        print_list(aux1);

        printf("\nNeighbours of vertex %i:\n", aux2->vertex.id);
        print_list(aux2);

        destroy(aux);

        destroy(con);
        destroy(dis);
        destroy(inter);
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