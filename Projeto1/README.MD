# Projeto 1
## Modelagem e conceitos fundamentais de grafos
Este projeto consiste na montagem de um grafo não direcionado, sem peso e que utiliza lista de adjacência, a partir do
arquivo ```data/karate.gml```. Com o grafo, calculamos/imprimimos: os vértices e seus respectivos graus, todos os
cliques maximais o coeficiente de aglomeração de cada vértice e o coeficiente médio de aglomeração do grafo.

### Autores:
 * 16/0141575: Pedro Lucas Silva Haga Torres
 * 14/0163603: Thales Gonçalves Grilo

In compliance with the documentation found within `data/` directory, we hereby cite "W. W. Zachary, An information flow
model for conflict and fission in small groups, Journal of Anthropological Research 33, 452-473 (1977)", since we're
using Zachary's data in order to model the graph this software uses.

### Instruções de Compilação e Execução:

Um `makefile` encontra-se na pasta `cmake-build-debug`. uma vez compilado, o comando ./projeto1 seria capaz de executá-lo.
Assim, a partir da pasta presente, o seguinte comando pode ser chamado:

  * `cd cmake-build-debug && make && ./projeto1`