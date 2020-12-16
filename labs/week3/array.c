//
// Created by Daniel Lucas on 08/11/2020.
//

#include <stdio.h>

/**
 * Reads the line from terminal.
 *
 * @param s char array of length MAX
 * @param MAX limit of characters to be stored
 * @return int length of char array s
 */
int readLine(char *s, int MAX) {
    int c;
    int sLen = 0;

    while ((c = getchar()) != '\n' && sLen < MAX) {
        *(s + sLen) = c;
        sLen++;
    }
    *(s + sLen) = '\0'; // null terminating string

    return sLen;
}

/**
 * Gets a single int from string. Stops at spaces ' '.
 *
 * @param s char array of ints
 * @param pPos position to start looking for int in char array s
 * @param len length of char array s
 * @return int value extracted from char array
 */
int getInt(char *s, int *pPos, int len) {
    int val = 0;

    while (*pPos < len && *(s + *pPos) != ' ') {
        if (*(s + *pPos) >= '0' && *(s + *pPos) <= '9') {
            val = (val * 10) + (*(s + *pPos) - '0');
        }
        (*pPos)++;
    }
    (*pPos)++;

    return val;
}

/**
 * Breaks apart char array s by ints and stores in int array a
 *
 * @param s char array of ints
 * @param len max length of char array s
 * @param a int array to store ints in
 * @param N Maximum length of int array a
 * @return int length of int array a
 */
int loadVector(char *s, int len, int *a, int N) {
    int pos = 0;
    int aLen = 0;

    while (pos < len && aLen < N) {
        *(a + aLen) = getInt(s, &pos, len);
        aLen++;
    }

    return aLen;
}

/**
 * Calculates the squared norm vector.
 * (The sum of each element squared).
 *
 * @param a int array of values
 * @param len length of int array
 * @return the squared norm of int array a
 */
long computeNorm(int *a, int len) {
    long norm = 0;
    for (int n = 0; n < len; n++) {
        norm = norm + *(a + n) * *(a + n);
    }
    return norm;
}

/**
 * Prints the vector of passed int array a.
 * Also prints values of int array a.
 *
 * @param a int array to display
 * @param len length of int array
 */
void printVector(int *a, int len) {
    for (int i = 0; i < len; i++) {
        printf("a[%d] = %d\n", i, *(a + i));
    }
    printf("<a,a> = %lu\n", computeNorm(a, len));
}

/**
 * Calculates and prints vector squared norm from input string.
 *
 * @return null
 */
int main() {
    int MAX = 100;
    int N = 10;

    char s[MAX];
    int a[N];

    int len = readLine(s, MAX);
    int aLen = loadVector(s, len, a, N);

    printf("input: %s\n", s);
    printVector(a, aLen);
}