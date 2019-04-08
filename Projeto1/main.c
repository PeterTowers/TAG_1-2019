/* Universidade de Brasília
 *
 * Disciplina: Teoria e Aplicação de Grafos - Turma A, 01/2019
 *
 * Projeto 1 - Modelagem e conceitos fundamentais de grafos
 *
 * Este programa utiliza o arquivo './data/karate.gml' para montar um grafo não direcionado, sem peso, utilizando lista
 * de adjacência. Com o grafo, calculamos/imprimimos:
 * (1) os vértices e seus respectivos graus;
 * (2) todos os cliques maximais;
 * (3) o coeficiente de aglomeração de cada vértice; e
 * (4) o coeficiente médio de aglomeração do grafo.
 *
 * Autores:
 * Pedro Lucas Silva Haga Torres - 16/0141575
 * Thales Gonçalves Grilo        - 14/0163603
 *
 * Código criado em 29/03/2019, disponível em: https://github.com/PeterTowers/TAG_1-2019/tree/master/Projeto1
 * ---------------------------------------------------------------------------------------------------------------------
 * ~~~~~~~~~> ATENÇÃO <~~~~~~~~~
 * Para alterar o local onde o arquivo karate.gml se encontra, basta trocar o segundo parâmetro da função load() onde
 * lê-se "./data/karate.gml"
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

    // Gera o grafo utilizando a função load() passando o diretorio onde o arquivo karate.gml está
    if(load(&network, "../data/karate.gml") != 0) exit(-1);

    question1(network);     // Objetivo (1) do projeto

    question2(&network);    // Objetivo (2) do projeto

    question3(&network);    // Objetivo (3) do projeto

    question4(&network);    // Objetivo (4) do projeto

    return (cleanup(&network) ? -3 : 0);    // Retorna 0 caso bem sucedido ou -3 caso haja um erro em cleanup()
}