//
// Created by Daniel Lucas on 15/11/2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXCHARS 100
#define MAXNUMBERS 10

int readLine(char *s, int max) {
    char c;
    char cOld = ' ';
    int i = 0;
    while ((c = getchar()) != '\n') {
        if (c != ' ' || cOld != ' ') {
            *s = c;
            s++;
            i++;
        }
        cOld = c;
    }
    if (*(s - 1) == ' ') {
        s--;
        i--;
    }
    *s = '\0';
    return i;
}

int getInt(char *s, int *n, int *pos) {
    char c;
    *n = 0;
    s = s + *pos;
    while ((c = *s) != ' ' && c != '\0') {
        if (c <= '9' && c >= '0') {
            *n = *n * 10 + c - '0';
        }
        s++;
        (*pos)++;
    }
    s++;
    (*pos)++;
    if (c == '\0') return 1;
    else return 0;
}

int getFloat(char *s, float *n, int *pos) {
    char c;
    int dec = 0;
    int factor = 1;
    *n = 0;
    s = s + *pos;
    while ((c = *s) != ' ' && c != '\0') {
        if (c == '.') dec = 1;
        if (c <= '9' && c >= '0') {
            *n = *n * 10 + c - '0';
            if (dec > 0) factor = factor * 10;
        }
        s++;
        (*pos)++;
    }
    *n = *n / factor;
    s++;
    (*pos)++;
    if (c == '\0') return 1;
    else return 0;
}

int getIntegers(int *v, char *s, int MAX) {
    int j = 0;
    int stop = 0;
    int n;
    float nF;
    int pos = 0;
    int posF = 0;
    while (stop != 1 && j < MAX) {
        stop = getInt(s, &n, &pos);
        v[j++] = n;

        // calc float
        getFloat(s, &nF, &posF);
        printf("FLOAT: %.6f\n", nF);
    }
    return j;
}

void executeCommand(int *v, int len, char op) {
    int val = *(v + 0);
    printf("%d ", *(v + 0));

    for (int i = 1; i < len; i++) {
        if (op == '+') val = val + *(v + i);
        if (op == '-') val = val - *(v + i);
        if (op == '*') val = val * *(v + i);
        if (op == '/') val = val / *(v + i);
        if (op == '%') val = val % *(v + i);
        printf("%c %d ", op, *(v + i));
    }
    printf("= %d\n", val);
}

void printNumber(int *v, int len) {
    printf("(n1");
    for (int i = 2; i <= len; i++) {
        printf(", n%d", i);
    }
    printf(")=(%d", *(v + 0));
    for (int i = 1; i < len; i++) {
        printf(", %d", *(v + i));
    }
    printf(")\n");
}

int main() {
    printf("%d\n", strcmp("quiz", "quit"));
    char s[MAXCHARS];
    int v[MAXNUMBERS];
    //+, -, *, /, %
    char opDefault = '+';
    char op = opDefault;
    while (1) {
        printf("write quit to exit or enter two integers (%c): ", op);
        int len = readLine(s, MAXCHARS);
        if (!strcmp(s, "quit")) return 0;
        if (len == 1) op = *s;
        else {
            if (fork() == 0) {
                int len = getIntegers(v, s, MAXNUMBERS);
                printNumber(v, len);
                executeCommand(v, len, op);
                return 0;
            }
            wait(NULL);
            op = opDefault; // default operation
        }
    }
}