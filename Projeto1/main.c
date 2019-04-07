/* Universidade de Brasília
 *
 * Disciplina: Teoria e Aplicação de Grafos - Turma A, 01/2019
 *
 * Projeto 1 - Modelagem e conceitos fundamentais de grafos
 *
 * Este programa utiliza o arquivo './data/karate.gml' para montar um grafo não direcionado, sem peso, utilizando lista
 * de adjacência. Com o grafo,
 *  calculamos/imprimimos: os vértices e seus respectivos graus, todos os cliques maximais
 * o coeficiente de aglomeração de cada vértice e o coeficiente médio de aglomeração do grafo.
 *
 * Autores:
 * Pedro Lucas Silva Haga Torres - 16/0141575
 * Thales Gonçalves Grilo        - 14/0163603
 *
 * Código criado em 29/03/2019, disponível em: https://github.com/PeterTowers/TAG_1-2019
 * ---------------------------------------------------------------------------------------------------------------------
 * In compliance with the documentation, we hereby cite "W. W. Zachary, An information flow model for conflict and
 * fission in small groups, Journal of Anthropological Research 33, 452-473 (1977)", since we're using Zachary's data in
 * order to model the graph this software uses.
 * ---------------------------------------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "program.h"

int main() {
    NETWORK network;
    if(!load(&network, "../data/karate.gml")) exit(-1);

    print_vertices(network);


    question3(&network);
    question4(&network);

    return (cleanup(&network) ? 0 : -3);
}