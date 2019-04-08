#include "network.h"

#include "bklist.h"

// Função que conta todos os triangulos existentes a partir de um no, percorrendo dois vizinhos interligados
// Esse calculo torna-se a base do calculo do coeficiente de aglomeracao
int triangle_count(VERTEX pivot, NETWORK* network){
  int result = 0;
  if (network == NULL) return 0; // CLEANUP: probably unnecessary

  // Encontramos os vizinhos (i) do no original (pivot)
  BK_LIST *n = find_neighbours(network, NULL, pivot, 0);
  
  // Caso um no tenha menos de dois vizinhos, nao ha como calcular o coeficiente
  if (length(n) < 2) return -1;
  
  // Percorrimento da lista de vizinhos como segundos vertices do triangulo
  for(BK_LIST *i = n, *nn = NULL; i != NULL; i = i->next){

    // Encontramos os vizinhos de segundo grau (j) de cada vizinho (i)
    nn = find_neighbours(network, NULL, i->vertex, 0);

    // Percorrimento dos vizinhos de segundo grau como terceiros vertices
    for(BK_LIST *j = nn, *nnn = NULL; j != NULL; j = j->next){

      // Encontramows os vizinhos de terceiro grau (k) de cada vizinho de segundo grau (j)
      nnn = find_neighbours(network, NULL, j->vertex, 0);

      // Caso o no original (pivot) seja vizinho dos seus vizinhos de segundo grau
      // Ou seja, caso o pivot seja vizinho de terceiro grau dele proprio
      // Incrementamos o contador, contando o triangulo recem formado
      for(BK_LIST *k = nnn; k != NULL; k = k->next)
        if (k->vertex.id == pivot.id){
            #ifdef DEBUG_PRINT_TRIANGLES
            printf("\ttriangulo: %d -> %d -> %d -> %d\n", pivot.id, i->vertex.id, j->vertex.id, k->vertex.id);
            #endif

            result++;
        }
      destroy(nnn);
    }

    destroy(nn);
  }

  destroy(n);

  // Resultado e dividido por dois, pois cada triangulo foi contado duas vezes
  return result / 2;
};


// Calcula a aglomeracao em um dado triangulo, indicado pelo proprio indice na lista de nos da rede
float agglomeration(NETWORK* network, int index){
  VERTEX pivot = network->vertex[index];
  float t = (float) triangle_count(pivot, network);


  return (t < 0)
    ? 0.0
    : ((2.0 * t) / (float) (pivot.degree * (pivot.degree - 1)));
}

// Calcula a aglomeracao media em um grafo, somando individualmente as aglomeracoes de cada no
// E dividindo pela contagem total de nos
float avg_agglomeration(NETWORK* network){
  float acc = 0.0;

  for(int i = 0; i < network->nvertices; i++)
    acc += agglomeration(network, i);

  return acc / ((float) network->nvertices);
}