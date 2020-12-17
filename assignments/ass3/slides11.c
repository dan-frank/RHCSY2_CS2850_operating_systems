#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sayHello(int *n);

int sayHi(int *n);

int sayGoodbye(int i, int n1, int n2);

int main() {
    int nHello = 4, nHi = 2, i = 0;
    pthread_t t1;
    while (nHello + nHi > 1) {
        i++;
        printf("iteration %d (start):\n", i);
        pthread_create(&t1, NULL, (void *) sayHello, (int *) &nHello);
        pthread_join(t1, NULL);
        pthread_create(&t1, NULL, (void *) sayHi, (int *) &nHi);
        pthread_join(t1, NULL);
        sayGoodbye(i, nHello, nHi);
    }
    return 0;
}

int sayHello(int *n) {
    if (*n) (*n)--;
    for (int i = 0; i < *n; i++) {
        printf("%d−Hello\n", i + 1);
        sleep(i % 2);
    }
        return 0;
}

int sayHi(int *n) {
    if (*n)(*n)--;
    for (int i = 0; i < *n; i++) {
        printf("%d−Hi\n", i + 1);
        sleep(i % 3);
    }
    return 0;
}

int sayGoodbye(int i, int n1, int n2) {
    for (int j = 0; j < n1; j++) printf("%d−goodbye Hello Thread\n", j + 1);
    for (int j = 0; j < n2; j++) printf("%d−goodbye Hi Thread\n", j + 1);
    printf("iteration %d(end)\n", i);
    return 0;
}
