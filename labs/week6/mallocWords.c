//
// Created by Daniel Lucas on 07/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXCHARS 500

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

    if (sLen == MAX) {
        sLen = sLen - 1;
    }

    *(s + sLen) = '\0';

    return sLen;
}

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
 * Calculates the amount of words in and length of char array.
 * Amount of words is updated via a pointer.
 *
 * @param nWords number of words passed by pointer
 * @param s char array to calculate
 * @return length of the string (after removing last space)
 */
int countWords(int *nWords, char *s) {
    int lim = stringLength(s);
    *nWords = 0;
    int s1 = 0;
    int j = 0;
    while (j < lim) {
        s1 = 0;
        while ((*s != ' ') && (*s != '\n') && (j < lim)) {
            s++; // goes through string char by char
            j++; // updates counter
            s1++; // increments if char in word
        }
        s++;
        j++;
        if (s1 > 0)(*nWords)++; // increments number of words if characters exist in word
    }
    return j - 1;
}

/**
 * Separates words separated by ' ' from char array s and stores in a pointer char array t.
 *
 * @param t pointer char array to store words in
 * @param s char array to take words from
 * @return int amount of words saved in pointer char array t
 */
int getWords(char *t[], char *s) {
    int pos = 0;
    int start = 0;
    int count = 0;
    int sLen = stringLength(s);

    while (pos < sLen) {
        if (*(s + pos) == ' ') {
            *(s + pos) = '\0';
            *(t + count) = (s + start);

            count++;
            start = (pos + 1);
        }
        pos++;
    }
    *(t + count) = (s + start);
    count++;

    return count;
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
    char s[MAXCHARS];
    int count = 0;
    readLine(s, MAXCHARS);
    countWords(&count, s);
    if (count >= 1) {
        char **t = malloc(count * sizeof(*t));
        getWords(t, s);

        printWords(t, count);
        free(t);
    }
}