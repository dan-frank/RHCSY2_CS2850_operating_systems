#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sayHello(int *n);

int sayHi(int *n);

int sayGoodbye(int i, int n1, int n2);

pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    int i = 0;
    int a[2];
    a[0] = 4;
    a[1] = 2;
    pthread_t t1, t2;
    while(a[0] + a[1] > 1){
        i++;
        printf("iteration %d (start):\n", i);
        pthread_create(&t1, NULL, (void *) sayHello, (int *) a); pthread_create(&t2, NULL, (void *) sayHi, (int *) a); pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        sayGoodbye(i, a[0], a[1]);
    }

    return 0;
}

int sayHello(int *a) {
    int I = 0;
    pthread_mutex_lock(&r_mutex);
    if (a[0]) a[0] = a[0] - 1;
    I = a[0];
    pthread_mutex_unlock(&r_mutex);
    for (int i = 0; i < I; i++) {
        printf("%d-Hello\n", i + 1);
        sleep(i % 2);
    }
    return 0;
}

int sayHi(int *a) {
    int I = 0;
    pthread_mutex_lock(&r_mutex);
    if (a[1])a[1] = a[1] - 1;
    I = a[1];
    pthread_mutex_unlock(&r_mutex);
    for (int i = 0; i < I; i++) {
        printf("%d-Hi\n", i + 1);
        sleep(i % 3);
    }
    return 0;
}


int sayGoodbye(int i, int n1, int n2) {
    for (int j = 0; j < n1; j++) printf("%d-goodbye Hello Thread\n", j + 1);
    for (int j = 0; j < n2; j++) printf("%d-goodbye Hi Thread\n", j + 1);
    printf("iteration %d(end)\n", i);
    return 0;
}
