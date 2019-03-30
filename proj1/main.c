#include <stdio.h>
#include <stdlib.h>
#include "readgml.h"
#include "program.h"

int main() {
    FILE *fptr;
    NETWORK *network = malloc(sizeof(NETWORK));

    FILE *tmp;

    char c;
    char file[] = "../karate.gml";

    fptr = fopen(file, "r");

    if (fptr == NULL ) {
        printf("Cannot open file");
        exit(66);
    }

    tmp = fptr;
    while ((c = getc(tmp)) != EOF) putchar(c);
    if(read_network(network, fptr) != 0){
        printf("Could not read network");
        exit(77);
    }


    print_vertices(*network);

    free_network(network);
    fclose(fptr);

    return 0;
}