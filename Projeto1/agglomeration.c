#include "network.h"

#include "bklist.h"

int length(BK_LIST* list){
  return (list == NULL)
    ? 0
    : 1 + length(list->next);
}

int triangle_count(VERTEX pivot, NETWORK* network){
  int result = 0;
  if (network == NULL) return 0; // CLEANUP: probably unnecessary

  BK_LIST *neighbors = find_neighbours(network, NULL, pivot, 0);
  
  if (length(neighbors) < 2) return -1;
  
  for(BK_LIST *i = neighbors, *head = NULL; i != NULL; i = i->next){
    head = find_neighbours(network, NULL, i->vertex, 0);

    for(BK_LIST *j = head; j != NULL; j = j->next)
      if (j->vertex.id == pivot.id)
          result++;

    destroy(head);
  }

  destroy(neighbors);
  return result / 2;
  /** Since every triangle is counted twice, we divide the result by 2
   *  This avoids an otherwise unnecessary and horrendous allocation nightmare to check each triangle
   */
};

float agglomeration(NETWORK* network, int index){
  VERTEX pivot = network->vertex[index];
  float t = (float) triangle_count(pivot, network);


  return (t < 0)
    ? 0.0
    : ((2.0 * t) / (float) (pivot.degree * (pivot.degree - 1)));
}

float avg_agglomeration(NETWORK* network){
  float acc = 0.0;

  for(int i = 0; i < network->nvertices; i++)
    acc += agglomeration(network, i);

  printf("acc: %f\n", acc);
  return acc / ((float) network->nvertices);
}