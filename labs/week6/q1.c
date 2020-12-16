//
// Created by Daniel Lucas on 10/11/2020.
//

#include <stdio.h>

struct point {
    int x;
    int y;
    int z;
};
struct pentagon{
    struct point x1;
    struct point x2;
    struct point x3;
    struct point x4;
    struct point x5;
};

int main() {
    struct pentagon ppp[3];
    printf("size of ppp: %lu\n", sizeof(ppp));
}