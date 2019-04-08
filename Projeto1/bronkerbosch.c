#include "bronkerbosch.h"

// A função bron_kerbosch() utiliza o algoritmo de Bron-Kerbosch com pivô para calcular e imprimir todos os cliques
// maximais do grafo. A nomenclatura utilizada aqui está de acordo com o pseudocódigo disponível na página da Wikipedia
// (https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm - visitada em 07/04/2019 às 22:45) de nome
// BronKerbosch2.
void bron_kerbosch(BK_LIST* group_r, BK_LIST* group_p, BK_LIST* group_x, NETWORK* network) {
    if ((group_p == NULL) && (group_x == NULL)) {   // Condição de parada da recursão
        printf("\n");
        printf("Clique maximal encontrado entre os vértices:\n");   // Imprime os vértices que fazem parte do clique
        print_list(group_r);
        printf("\n");

        return; // Pára a execução da função e retorna para a chamada superior
    }

    VERTEX pivot = find_greatest_degree(algebraic_union(group_p, group_x)); // Define o vértice pivô 'u'

    // Gera uma lista contendo os vértices vizinhos de 'u', N(u)
    BK_LIST* pivot_neighbours = find_neighbours(network, NULL, pivot, 0);

    // Cria uma lista de vértices chamada 'v', definida como v := P \ N(u)
    BK_LIST* group_v = clone(group_p);
    while (pivot_neighbours != NULL) {
        group_v = disjunction(group_v, pivot_neighbours->vertex);
        pivot_neighbours = pivot_neighbours->next;
    }

    // Laço para iterar por cada vértice de 'v'
    while (group_v != NULL) {
        // Define uma lista de vizinhos de cada vértice 'v', chamada N(v)
        BK_LIST* v_neighbours = find_neighbours(network, NULL, group_v->vertex, 0);

        // Faz a chamada recursiva da função passando como parâmetros: R ⋃ {v}, P ⋂ N(v), X ⋂ N(v)
        bron_kerbosch(conjunction(group_r, group_v->vertex), intersection(group_p, v_neighbours),
                intersection(group_x, v_neighbours), network);

        // Define a lista P do algoritmo como P := P \ {v}
        group_p = disjunction(group_p, group_v->vertex);

        // Define a lista X do algoritmo como X := X ⋃ {v}
        group_x = conjunction(group_x, group_v->vertex);

        // Define o próximo elemento da lista {v}
        group_v = group_v->next;
    }

    return; // Sai da função retornando para uma instância superior
}

// Função para encontrar os cliques maximais fazendo a chamada inicial de bron_kerbosch()
int max_clique(NETWORK* network) {
    BK_LIST* candidates = generate_list(network, NULL, 0);  // Cria e inicializa a lista de vértices

    // Chamada inicial de bron_kerbosch(), passando NULL para indicar as listas vazias
    bron_kerbosch(NULL, candidates, NULL, network);
    
    // Chama a função de limpeza de memória
    destroy(candidates);

    // Retorna 0 indicando uma execução sem problemas
    return 0;
}