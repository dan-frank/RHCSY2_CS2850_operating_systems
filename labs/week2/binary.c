//
// Created by Daniel Lucas on 08/11/2020.
//

#include <stdio.h>

int getbits(unsigned x, int p){
    int mask = ~((unsigned) ~0 << 1);
    x = x >> p;
    x = x & mask;
    return x;
}

int main() {
    printf("Binary\n");

    int c;
    int n = 10;
    int array[n];
    int val = 0;

    int i = 0;
    while ((c = getchar()) != '\n' && i < n) {
        if (c >= '0' && c <= '9') {
            array[i] = c - '0';
            val = (val * 10) + array[i];
            i++;
        }
    }
    printf("Val:    %d\n", val);

    printf("Binary: ");
    for (int j = 7; j > 0; j--) {
        printf("%o", getbits(val, (j - 1)));
    }
    printf("\n");
}