#include <stdio.h>
#include <stdlib.h>
#include "readgml.h"

int main() {
    FILE *fptr;
    NETWORK *network;

    int a;
    char file[] = "/home/pedro/Documents/TeoAppGrafos/proj1/karate.gml";

    printf("Hello, World!\n");

    fptr = fopen(file, "r");

    if (fptr == NULL ) {
        printf("Cannot open file");
        exit(66);
    }

    a = read_network(network, fptr);

    if (a == 0)
        printf("Deu certo!");
    else
        printf("Nao deu certo :(");

    free_network(network);
    fclose(fptr);

    return 0;
}