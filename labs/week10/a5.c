//
// Created by Daniel Lucas on 08/12/2020.
//

#include <stdio.h>

#define MAXCHARS 100

void quicksort(char *s, int len);

void swapEntries(char *s, int i, int j);

int main(void) {
    char *s = "A pointer is a variable that contains an address";
    int i = 0;
    while (*(s + i) != '\0' && i < MAXCHARS) i++;
    int n = i - 1;
    quicksort(s, n);
    printf("%s\n", s);
    return 0;
}

void swapEntries(char *s, int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void quicksort(char *s, int len) {
    if (len < 2) return;
    char pivot = s[len / 2];
    int i, j;
    for (i = 0, j = len - 1;; i++, j--) {
        while (s[i] < pivot) i++;
        while (s[j] > pivot) j--;
        if (i >= j) break;
        swapEntries(s, i, j);
    }
    quicksort(s, i);
    quicksort(s + i, len - i);
}