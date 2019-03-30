#include <stdio.h>
#include <stdlib.h>
#include "program.h"

int main() {
    NETWORK network;
    if(!load(&network, "../karate.gml")) exit(-1);

    print_vertices(network);

    return (cleanup(&network) ? 0 : -3);
}