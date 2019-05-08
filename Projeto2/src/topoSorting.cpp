//
// Created by pedro on 07/05/19.
//

#include <vector>
#include "../include/topoSorting.hpp"
#include "../include/graph.hpp"
#include "../include/course.hpp"


/* ========== KAHN'S ALGORITHM ==========
 *
 * L ← Empty list that will contain the sorted elements
 * S ← Set of all nodes with no incoming edge
 *
 * while S is non-empty do
 *      remove a node n from S
 *      add n to tail of L
 *
 *      for each node m with an edge e from n to m do
 *          remove edge e from the graph
 *
 *          if m has no other incoming edges then
 *              insert m into S
 *
 *          if graph has edges then
 *              return error   (graph has at least one cycle)
 *
 *          else
 *              return L   (a topologically sorted order)
 *
 * ====================================== */

int topo_sorting(digraph<course>* graph) {
    // TODO: receive/create graph
    digraph<course> list_l;
    digraph<course> list_s = graph->root_nodes(); // DONE: Filter graph for nodes with no incoming edge

    list_s.cp_edges(graph);
    list_s.print_adj();     // For test purpose only
    // TODO: Run Kahn's algorithm

    return 0;
}

void kahn(digraph<course>* digraph);