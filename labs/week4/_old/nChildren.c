#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void taskFunction(int sec, int n) {
    printf("%dth child (pid=%d) sleeps for %d seconds\n", n, getpid(), sec);
    sleep(sec);
    printf("- %dth exits\n", n);
}

int main(int argc, char **argv) {
    char *p;
    int N = strtol(argv[1], &p, 10);

    for (int n = 0; n < N; n++) {
        if (fork() == 0) {
            int sec = N * (n % 3);
            taskFunction(sec, (n + 1));
            return 0;
        }
    }

    wait(NULL);
    return 0;
}