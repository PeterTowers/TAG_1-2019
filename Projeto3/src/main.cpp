/* Universidade de Brasília
 *
 * Disciplina: Teoria e Aplicação de Grafos - Turma A, 01/2019
 *
 * Projeto 2 - Ordernacão topológica e caminho crítico em um DAG
 *
 * Este programa utiliza o arquivo './data/materias.txt' para montar um dígrafo com peso, utilizando lista de
 * adjacência. Implementamos as seguintes funções sobre o dígrafo:
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
 * Código criado em 03/05/2019, disponível em: https://github.com/PeterTowers/TAG_1-2019/tree/master/Projeto2
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

    // matrix->flipped().inspect();

    // // Prints graph onscreen in terminal
    // graph->print_adj();

    // // Prints sorted graph (sorted by topological sorting)
    // graph->print_ordered(print_course);
    // graph->critical_path();

    return 0;
}
