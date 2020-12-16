//
// Created by Daniel Lucas on 08/12/2020.
//

#include <stdio.h>

#define n 15

void quicksort(int *a, int len);

void swapEntries(int *a, int i, int j);

int main(void) {
    int a[n];
    *(a + n - 1) = 0;
    *(a + n - 2) = 1;
    for (int i = n - 3; i >= 0; i--) *(a + i) = *(a + i + 1) + *(a + i + 2);
    int i;
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    quicksort(a, n);
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

void quicksort(int *a, int len) {
    if (len < 2) return;
    int pivot = a[len / 2];
    int i, j;
    for (i = 0, j = len - 1;; i++, j--) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i >= j) break;
        swapEntries(a, i, j);
    }
    quicksort(a, i);
    quicksort(a + i, len - i);
}

void swapEntries(int *a, int i, int j) {
    int t = *(a + i);
    *(a + i) = *(a + j);
    *(a + j) = t;
}