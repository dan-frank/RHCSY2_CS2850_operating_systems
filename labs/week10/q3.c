//
// Created by Daniel Lucas on 08/12/2020.
//

#include <stdio.h>

int main() {
    for (int i = 0; i < 100; i++) {
        char *s = "A pointer is a variable that contains an address";
        char c = s[i + 1];
        s = s + i;
        if (c - *s == 84) {
            printf("[i = %d] c - *s = %d\n", i, c - *s);
        }
    }

    for (int i = 0; i < 100; i++) {
        int a[100];
        *a = 0;
        *(a+1) = 1;
        for (int k=2; k<100;k++)
            *(a+k) = *(a+k-1) + *(a+k-2);
        int j = 0;
        while (*(a+j + 1) < 5 * i ) j++;
        if (5 * i - a[j] == 10) {
            printf("[i = %d] 5 * i - a[j] = %d\n", i,  5 * i - a[j]);
        }
    }
    return 0;
}