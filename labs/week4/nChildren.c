//
// Created by Daniel Lucas on 08/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *p;
    int N = strtol(argv[1], &p, 10);

    printf("int: %d\n", N);
}