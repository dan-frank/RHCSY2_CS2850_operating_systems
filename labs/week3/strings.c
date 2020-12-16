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
 * Separates words separated by ' ' from char array s and stores in a pointer char array t.
 *
 * @param t pointer char array to store words in
 * @param s char array to take words from
 * @param MAXWORDS total words allowed in
 * @return int amount of words saved in pointer char array t
 */
int getWords(char *t[], char *s, int MAXWORDS) {
    int pos = 0;
    int start = 0;
    int count = 0;
    int sLen = stringLength(s);

    while (count < MAXWORDS && pos < sLen) {
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
void printVector(char **t, int size) {
    for (int k = 0; k < size; k++) {
        printf("w%d: %s (%d)\n", k + 1, *(t + k), stringLength(*(t + k)));
    }
}

/**
 * Calculates length of words passed as char array.
 * // Commented out code gets string from terminal
 * Left code gets from command line argument
 *
 * @return null
 */
int main(int argc, char *argv[]) {
//    int MAXCHARS = 100;
//    int MAXWORDS = 10;

//    char s[MAXCHARS];
//    char *t[MAXWORDS];

//    readLine(s, MAXCHARS);
//    int tLen = getWords(t, s, MAXWORDS);
//    printVector(t, tLen);

    printVector((argv + 1), (argc - 1));
}