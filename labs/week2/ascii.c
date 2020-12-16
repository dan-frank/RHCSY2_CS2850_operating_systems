//
// Created by Daniel Lucas on 08/11/2020.
//

#include <stdio.h>

int lower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}

int upper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    } else {
        return c;
    }
}

int main() {
    int c;
    int n = 10;
    char string[n];
    int i = 0;
    while ((c = getchar()) != EOF && i < n) {
        string[i] = upper(c);
        i++;
    }
    printf("%s\n", string);
}