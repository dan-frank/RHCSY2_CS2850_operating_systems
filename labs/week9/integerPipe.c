//
// Created by Daniel Lucas on 24/11/2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int getInteger(int *end) {
    (*end) = -1;
    return 25;
}

int writeMessage(FILE *pipeEnd, int n, int end) {
    fwrite(&n,  sizeof(int), 1, pipeEnd);
    if (end != 0) {
        fwrite(&end, sizeof(int), 1, pipeEnd);
    }
    return n;
}

int readMessage(FILE *pipeEnd, int *sum) {
    int y;
    int offset = sizeof(int) * (*sum);
    fread(&y, sizeof(int), offset, pipeEnd);
    printf("We just read y: %d\n", y);

    if (y == -1) {
        return -1;
    }

    (*sum) = (*sum) + y;
    return 0;
}

int main() {
    int fd[2];
    int good = pipe(fd);
    if (good == -1) {
        printf("An error occurred when opening the pipe\n");
        return 1;
    }

    FILE *readEnd = fdopen(fd[0], "r");
    FILE *writeEnd = fdopen(fd[1], "w");

    int pid = fork();
    if (pid == 0) {
        fclose(readEnd);
        int end = 0;
        while (end == 0) {
            int n = getInteger(&end);
            writeMessage(writeEnd, n, end);
        }
        fclose(writeEnd);
    } else {
        fclose(writeEnd);
        int end = 0;
        int sum = 0;
        while (end == 0) {
            end = readMessage(readEnd, &sum);
            printf("sum = %d \n", sum);
        }
        fclose(readEnd);
    }

    wait(NULL);
    return 0;
}