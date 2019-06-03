/* Universidade de Brasília
 *
 * Disciplina: Teoria e Aplicação de Grafos - Turma A, 01/2019
 *
 * Projeto 3 - Problema de pareamento
 *
 * Este programa utiliza o arquivo './data/data.txt' para montar um grafo não direcionado e sem peso. Sobre esse grafo,
 * implementamos o cálculo de pareamento utilizando o algoritmo descrito no artigo "Two Algorithms for the
 * Student-Project Allocation Problem" de  ABRAHAM, D. J.; IRVING, R. W.; MANLOVE, D. F.
 *
 * TODO: terminar descrição
 * (1) ordenação topológica;
 * (2) caminho crítico; e
 * (3) impressão dos arquivos '.dot' do:
 *      (3.1) Dígrafo ('../data/adjacency_list.dot');
 *      (3.2) A ordenação topológica do dígrafo ('../data/topological_order');
 *      (3.4) Caminho crítico  do dígrafo ('../data/critical_path').
 *
 * Para maiores informações sobre o cálculo do caminho crítico e sobre a impressão do dígrafo como imagem, leia o
 * arquivo README.MD.
 *
 * Autores:
 * Pedro Lucas Silva Haga Torres - 16/0141575
 * Thales Gonçalves Grilo        - 14/0163603
 *
 * Código criado em 03/05/2019, disponível em: https://github.com/PeterTowers/TAG_1-2019/tree/master/Projeto3
 * ---------------------------------------------------------------------------------------------------------------------
 * ~~~~~~~~~> ATENÇÃO <~~~~~~~~~
 * TODO: esse campo é necessário?
 *
 * ---------------------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include "../include/reader.hpp"
#include "../include/Graph.hpp"
#include "../include/Matrix.hpp"

int main(int argc, char const *argv[]){

    // Builds the graph onto object 'graph'
    Graph* graph = new Graph;
    Matrix<Teacher, School>* matrix = new Matrix<Teacher, School>();

    build("data/data.txt", graph, matrix);

    graph->inspect();

    matrix->inspect();

    // Printing result
    // unsigned int school_id = 0;
    for (auto& edge : matrix->pairing())
      std::cout << edge.from() << ": " << edge.to() << std::endl;

    return 0;
}
