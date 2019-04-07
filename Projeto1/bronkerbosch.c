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

//void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x, NETWORK* network) {
//    if ((group_p == NULL) && (group_x == NULL)) {
//        printf("[bron_kerbosch] Maximal clique found between vertexes:\n");
//        print_list(group_r);
//        printf("\n");
//    }
//
//    VERTEX pivot = find_greatest_degree(algebraic_union(group_p, group_x));
//
//    BK_LIST* pivot_neighbours;
//    neighbours->vertex = network->vertex[pivot.edge[0].target];
//    neighbours->next = malloc(sizeof(BK_LIST));
//    neighbours->next = find_neighbours(network, neighbours, pivot, 1);
//
//    BK_LIST* group_v;
//
//    while (neighbours != NULL) {
//        group_v = disjunction(group_p, neighbours->vertex);
//        neighbours = neighbours->next;
//    }
//
//    while (group_v != NULL) {
//        BK_LIST* v_neighbours;
//        v_neighbours->vertex = network->vertex[group_v->vertex.edge[0].target];
//        v_neighbours->next = malloc(sizeof(BK_LIST));
//        v_neighbours->next = find_neighbours(network, v_neighbours, group_v->vertex, 1);
//
//        bron_kerbosch(conjunction(group_r, group_v->vertex), intersection(group_p, v_neighbours),
//                intersection(group_x, v_neighbours), network);
//
//        group_p = disjunction(group_p, group_v->vertex);
//        group_x = conjunction(group_x, group_v->vertex);
//
//        group_v = group_v->next;
//    }
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

        printf("---------------- TESTING ALGEBRAIC_UNION\n");
        BK_LIST* alg_union = clone(candidates);
        BK_LIST* alg_union2 = clone(candidates);        // Não sei porque não está sendo tradado como uma lista indep. - Pedro

        VERTEX vertex1 = network->vertex[15];
        VERTEX vertex2 = network->vertex[10];
        VERTEX vertex3 = network->vertex[18];
        VERTEX vertex4 = network->vertex[9];

        alg_union = disjunction(alg_union, vertex);
        alg_union = disjunction(alg_union, vertex1);
        alg_union = disjunction(alg_union, vertex2);

        alg_union2 = disjunction(alg_union, vertex3);
        alg_union2 = disjunction(alg_union, vertex4);

        BK_LIST* unionized;
        unionized = algebraic_union(alg_union, alg_union2);

        printf("vertexes removed from alg_union: %i, %i, %i\n", vertex.id, vertex1.id, vertex2.id);
        printf("alg_union:\n");
        print_list(alg_union);
        print_list(unionized);
        printf("above, unionized list\n");

        printf("vertexes removed from alg_union2: %i, %i\n", vertex3.id, vertex4.id);
        printf("alg_union2:\n");
        print_list(alg_union2);

        printf("candidates list:\n");
        print_list(candidates);

        destroy(alg_union);
        destroy(alg_union2);
        destroy(unionized);

        printf("---------------- TESTING FIND_NEIGHBOURS\n");
        BK_LIST* aux;
        BK_LIST* aux1;
        BK_LIST* aux2;

        VERTEX vertex6 = candidates->vertex;
        VERTEX vertex7 = candidates->next->vertex;
        VERTEX vertex8 = candidates->next->next->vertex;

        aux = find_neighbours(network, NULL, vertex6, 0);
        printf("\nNeighbours of vertex %i:\n", vertex6.id);
        print_list(aux);

        aux1 = find_neighbours(network, NULL, vertex7, 0);
        printf("\nNeighbours of vertex %i:\n", vertex7.id);
        print_list(aux1);

        aux2 = find_neighbours(network, NULL, vertex8, 0);
        printf("\nNeighbours of vertex %i:\n", vertex8.id);
        print_list(aux2);

        destroy(aux);
        destroy(aux1);
        destroy(aux2);

        printf("---------------- TESTING FIND_GREATEST_DEGREE\n");
        BK_LIST* aux4 = NULL;

        VERTEX greatDegree = find_greatest_degree(aux4);

        printf("NULL list vertex degree: %i\n", greatDegree.degree);

        aux4 = clone(candidates);
        greatDegree = find_greatest_degree(aux4);
        printf("Greatest degree vertex: %i.\t\tDegree: %i\n", greatDegree.id, greatDegree.degree);

        aux4 = disjunction(aux4, greatDegree);
        greatDegree = find_greatest_degree(aux4);
        printf("2nd greatest degree vertex: %i.\tDegree: %i\n", greatDegree.id, greatDegree.degree);

        aux4 = disjunction(aux4, greatDegree);
        greatDegree = find_greatest_degree(aux4);
        printf("3rd greatest degree vertex: %i.\tDegree: %i\n", greatDegree.id, greatDegree.degree);

        destroy(aux4);

        printf("---------------- TESTING BRON_KERBOSCH\n");
        //bron_kerbosch(NULL, candidates, NULL, network);

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