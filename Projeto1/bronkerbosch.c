#include "bronkerbosch.h"

#define TEST_LIST_FUNCTIONS

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

void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x, NETWORK* network) {
    if ((group_p == NULL) && (group_x == NULL)) {
        printf("[bron_kerbosch] Maximal clique found between vertexes:\n");
        print_list(group_r);
        printf("\n");

        return;
    }

    VERTEX pivot = find_greatest_degree(algebraic_union(group_p, group_x)); // pivot vertex 'u'

    BK_LIST* pivot_neighbours = find_neighbours(network, NULL, pivot, 0);   // neighbour vertexes of 'u', N(u)

    // Now we create a list of vertices v := P \ N(u)
    BK_LIST* group_v = clone(group_p);
    while (pivot_neighbours != NULL) {
        group_v = disjunction(group_v, pivot_neighbours->vertex);
        pivot_neighbours = pivot_neighbours->next;
    }

    // Here we iterate through each vertex found in v
    while (group_v != NULL) {
        // We need to define a list of neighbours of each vertex v, N(v)
        BK_LIST* v_neighbours = find_neighbours(network, NULL, group_v->vertex, 0);

        // Recursive call on Bron-Kerbosch algorithm passing these parameters: R ⋃ {v}, P ⋂ N(v), X ⋂ N(v)
        bron_kerbosch(conjunction(group_r, group_v->vertex), intersection(group_p, v_neighbours),
                intersection(group_x, v_neighbours), network);

        group_p = disjunction(group_p, group_v->vertex);    // P := P \ {v}
        group_x = conjunction(group_x, group_v->vertex);    // X := X ⋃ {v}

        group_v = group_v->next;    // Set the next element of list {v}
    }

    return;
}

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
        bron_kerbosch(NULL, candidates, NULL, network);

        destroy(con);
        destroy(dis);
        destroy(inter);
        free(nil1);
        free(nil2);
    #endif

    return 0;
}