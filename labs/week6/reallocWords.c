//
// Created by Daniel Lucas on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 100

/**
 * Calculates the length of a char array.
 *
 * @param s char array to calculate
 * @return int length of string array
 */
int stringLength(char *s) {
    int count = 0;

    while (1) {
        if (*(s + count) == '\0') {
            return count;
        }
        count++;
    }
}

/**
 * Reads a single word from input.
 *
 * @param buf char array to read from
 * @param end true/false for end of char array
 * @param maxLength max length of char array
 * @return length of word
 */
int getWord(char *buf, int *end, int maxLength) {
    int j = 0;
    char c;
    while (((c = getchar()) != ' ') && (c != '\n') && (j < maxLength)) {
        buf[j++] = c;
    }
    if (c == '\n') *end = 1;
    return j;
}

/**
 * Copy string from one char array to another.
 *
 * @param in char array to copy from
 * @param out char array to copy to
 * @return int size of copied string
 */
int copyString(char *in, char *out) {
    int i = 0;
    while (in[i] != '\0') {
        out[i] = in[i];
        i++;
    }
    out[i] = '\0';
    return i;
}

/**
 * Prints words and their length.
 *
 * @param t pointer char array of words
 * @param size amount of words to print
 */
void printWords(char **t, int size) {
    for (int k = 0; k < size; k++) {
        printf("%d-th word: %s (%d)\n", k + 1, *(t + k), stringLength(*(t + k)));
    }
}

int main() {
    char buf[MAXLENGTH];
    int end = 0;
    int count = 0;
    char **t = malloc(sizeof(char**));
    while (end != 1) {
        int j = getWord(buf, &end, MAXLENGTH);
        if (j > 0) {
            buf[j] = '\0';
            t = realloc(t, j);
            t[count] = malloc((stringLength(buf) + 1) * sizeof(char));
            copyString(buf, t[count]);
            count = count + 1;
        }
    }
    printWords(t, count);
    for (int i = 0; i < count; i++) {
        free(*(t + i));
    }
}