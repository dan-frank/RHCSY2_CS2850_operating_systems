#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHARS 500
#define MAXLENGTH 100
#define MAXWORDS 10

int stringLength(char *s) {
    int count = 0;

    while (1) {
        if (*(s + count) == '\0') {
            return count;
        }
        count++;
    }
}

int readLine(char *s, int MAX) {
    int i = 0;
    int c;
    while ((c = getchar()) != '\n' || i == MAX) {
        *(s + i) = c;
        i++;


    }
    if (i == MAX) {
        i = i - 1;

    }
    *(s + i) = '\0'; // null terminating string
    return i;

}

int countWords(int *nWords, char *s) {
    int lim = stringLength(s);
    *nWords = 0;
    int sl = 0;
    int j = 0;
    while (j < lim) {
        sl = 0;
        while ((*s != ' ') && (*s != '\n') && (j < lim)) {
            s++;
            j++;
            sl++;
        }
        s++;
        j++;
        if (sl > 0)(*nWords)++;

    }
    return j - 1;
}

int getWord(char *buf, int *end, int maxLength) {
    int j = 0;
    char c;
    while (((c = getchar()) != ' ') && (c != '\n') && (j < maxLength)) {
        buf[j++] = c;
    }
    if (c == '\n') *end = 1;
    return j;
}


int getWords(char **t, char *s, int nWords) {
    int len = 0;
    int pos = 0;
    int start = 0;
    int sLen = stringLength(s);
    while (len < MAXWORDS && pos < sLen) {
        if (*(s + pos) == ' ') {
            *(s + pos) = '\0';
            *(t + len) = (s + start);


            len++;
            start = (pos + 1);
        }

        pos++;


    }

    *(t + len) = (s + start);


    len++;

    return len;

}

void printWords(char **t, int size) {
    for (int k = 0; k < size; k++) {
        printf("%d-th word: %s (%d)\n", k + 1, *(t + k), stringLength(*(t + k)));
    }
}

int copyString(char *in, char *out) {
    int i = 0;
    while (in[i] != '\0') {
        out[i] = in[i];
        i++;
    }
    out[i] = '\0';
    return i;
}

int main() {

    char buf[MAXLENGTH];
    int end = 0;
    int count = 0;
    char **t = malloc(sizeof(char **));
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
        free(t[count]);
    }
}