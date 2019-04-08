#include "bklist.h"

// Função para gerar uma lista de um unico elemento com o vértice passado
BK_LIST* new(VERTEX vertex) {
  BK_LIST *head;
  head = malloc(sizeof(BK_LIST));
  head->vertex = vertex;
  head->previous = NULL;
  head->next = NULL;
  return head;
}

// A função clone() clona uma lista para um outro endereço de memória
BK_LIST* clone(BK_LIST* list) {
    if (list == NULL) return NULL;    // Condição de parada da recursão
    BK_LIST *head;

    head = new(list->vertex);
    head->next = clone(list->next);   // Chamada recursiva passando o próximo elemento da lista

    // Define o endereço do elemento anterior do próximo elemento (next->previous) como o endereço do elemento
    // desta iteração
    if (head->next != NULL) head->next->previous = head;

    return head;
}

// conjunction() adiciona um vértice na última posição da lista
BK_LIST* conjunction(BK_LIST* list, VERTEX vertex) {

    // Caso a lista seja vazia, gera uma nova lista com o vértice passado
    if (list == NULL) {
        BK_LIST* newList = new(vertex);
        return newList;
    }

    // Gera duas novas cópias da lista passada
    BK_LIST* copy = clone(list);
    BK_LIST* last = copy;

    while(last->next != NULL) last = last->next;    // Procura o último elemento da lista
    last->next = new(vertex);                       // Acrescenta o elemento fazendo as atribuições necessárias
    last->next->previous = last;

    return copy;    // Retorna o ponteiro para o primeiro elemento da lista
}

// Retorna um "booleano" indicando se uma lista contém um elemento
int contains(BK_LIST* list, VERTEX vertex) {
    // Condição de parada da recursão: caso a lista seja vazia ou a chamada chegue ao final da lista, ela não contém o
    // elemento passado, portanto retorna 0 (falso)
    if (list == NULL) return 0;

    // Retorna 1 (!= 0, logo, verdadeiro) caso encontre o vértice, ou faz a chamada recursiva procurando no elemento
    // seguinte da lista
    return (list->vertex.id == vertex.id) || contains(list->next, vertex);
}

// Função para gerar uma lista contendo a interseção entre duas listas
BK_LIST* intersection(BK_LIST* list1, BK_LIST* list2) {
    // Condição de parada da recursão: uma interseção com lista vazia gera uma lista vazia
    if (list1 == NULL || list2 == NULL) return NULL;
  
    BK_LIST *head = NULL;           // Gera uma nova lista para armazenar a interseção
    VERTEX vertex = list1->vertex;  // Armazena o vértice da primeira lista recebida

    // Procura o vertice da lista1 na lista2 e, caso ele esteja contido, armazena na lista de interseções, fazendo as
    // atribuições necessárias
    if (contains(list2, list1->vertex)){
    head = new(vertex);
    head->next = intersection(list1->next, list2);
    if (head->next != NULL) head->next->previous = head;
    }
    else head = intersection(list1->next, list2);

    return head;
}

// Função para remover um elemento de uma lista
BK_LIST* disjunction(BK_LIST* list, VERTEX vertex) {
    // Condição de parada da chamada recursiva
    if (list == NULL) return NULL;

    // Procura o elemento na lista e ao encontra-lo, faz uma chamada recursiva passando o elemento seguinte da lista
    // de forma a fazer os ajustes necessários aos ponteiros.
    if (list->vertex.id == vertex.id) return disjunction(list->next, vertex);
    BK_LIST *head;

    head = new(list->vertex);
    head->next = disjunction(list->next, vertex);

    if (head->next != NULL) head->next->previous = head;

    return head;
}

// Função para fazer uma união algébrica entre duas listas
BK_LIST* algebraic_union(BK_LIST* list1, BK_LIST* list2) {
    // Caso uma das listas passadas esteja vazia, retorna a outra
    if (list1 == NULL)
        return list2;
    else if (list2 == NULL)
        return list1;

    // Caso as listas não sejam nulas, a lista1 é clonada e procura-se os elementos da lista2 que não estão na lista1
    // para acrescenta-los, retornando a lista com a união de ambas.
    else {
        BK_LIST *unionized = clone(list1);
        BK_LIST *aux = list2;

        while (aux != NULL) {
            if (contains(unionized, aux->vertex) != 0)
                conjunction(unionized, aux->vertex);

            aux = aux->next;
        }

        return unionized;
    }
}

// Função para imprimir os indices dos vértices dentro de uma lista
void print_list(BK_LIST* list) {
  BK_LIST* tracer = list;

  printf("[print_list] (");
  while(tracer != NULL){
    printf("%d", tracer->vertex.id);
    if (tracer->next != NULL) printf(", ");

    tracer = tracer->next;
  }
  printf(")\n");
}

// Função recursiva para criar uma lista de vértices a partir da network disponível
BK_LIST* generate_list(NETWORK* network, BK_LIST* list, int arrPosition) {
    // Condição de parada da chamada recursiva: chegar no último vértice da lista e retornar NULL para fechar a lista
    if (arrPosition == network->nvertices)
        return NULL;

    // Aloca espaço em memória para o primeiro elemento da lista e faz as definições necessárias para o funcionamento
    // da lista
    BK_LIST* newList = calloc(1, sizeof(BK_LIST));

    newList->previous = list;
    newList->vertex = network->vertex[arrPosition];
    newList->next = malloc(sizeof(BK_LIST));

    newList->next = generate_list(network, newList, ++arrPosition); //Chamada recursiva para o próximo elemento da lista

    return newList; // Retorna o endereço da lista criada na instância em execução
}

// Função para gerar uma lista de vértices vizinhos a um outro
BK_LIST* find_neighbours (NETWORK* network, BK_LIST* list, VERTEX vertex, int degree) {
    // Condição de parada da chamada recursiva: chegar no último vértice da lista de vizinhos. Ou, Caso o véritce não
    // tenha vizinhos, retorna NULL
    if ((degree == vertex.degree) || (vertex.degree == 0))
        return NULL;

    // Aloca espaço para o primeiro elemento da lista e faz as definições necessárias para o funcionamento da lista
    BK_LIST* neighbour = malloc(sizeof(BK_LIST));

    neighbour->previous = list;
    neighbour->vertex = network->vertex[vertex.edge[degree].target];
    neighbour->next = malloc(sizeof(BK_LIST));
    neighbour->next = find_neighbours(network, neighbour, vertex, ++degree);    // Chamada recursiva

    return neighbour;   // Retorna o endereço da lista criada na instância em execução
}

// Função para encontrar o vértice de maior grau dentro de uma lista
VERTEX find_greatest_degree (BK_LIST* list) {
    // Caso a lista esteja vazia, retorna um vértice com grau -1 indicando erro
    if (list == NULL) {
        VERTEX errVertex;
        errVertex.degree = -1;

        return errVertex;
    }
    // Declara uma lista auxiliar e um vértice para armazenar o vértice de maior grau
    BK_LIST* aux = list->next;
    VERTEX max = list->vertex;

    // Laço para percorrer a lista em busca do vértice de maior grau
    while (aux != NULL) {
        if (aux->vertex.degree > max.degree) {
            max = aux->vertex;
        }
        aux = aux->next;
    }

    return max;
}

// Função para desalocar a memória utilizada por uma lista
void destroy(BK_LIST* list) {
    if (list == NULL) return;   // Caso a lista passada esteja vazia, não é necessário desalocar seu espaço em memória

    BK_LIST *aux1, *aux2;

    aux1 = list;

    // Laço para chegar no primeiro elemento da lista
    while (aux1->previous != NULL)
        aux1 = aux1->previous;

    // Laço para desalocar a memória
    while (aux2 != NULL) {
        aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}