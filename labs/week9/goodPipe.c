//
// Created by Daniel Lucas on 26/11/2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
    if (c == '\0') return -1;
    else return 0;
}

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        printf("Error declaring pipe in main()\n");
        return -1;
    }

    int pid = fork();
    if (pid == 0) {
        close(fd[0]);
        char s[MAXCHARS];
        int len = readLine(s, MAXCHARS);
        int end = 0;

        while (end == 0) {
            int n;
            int pos = 0;
            end = getInt(s, &n, &pos);
            write(fd[1], &n, sizeof(int));
            printf("n = %d | pos = %d | len = %d\n", n, pos, len);
        }
        write(fd[1], &end, sizeof(int));
        close(fd[1]);
    } else {
        close(fd[1]);
        int sum = 1;
        int end = 0;
        while (end == 0) {
            int y;
            read(fd[0], &y, (sizeof(int) * sum));
            if (y == -1) {
                end = -1;
            } else {
                printf("Got from child: %d\n", y);
            }
            sum++;
        }

        close(fd[0]);
        wait(NULL);
    }
}