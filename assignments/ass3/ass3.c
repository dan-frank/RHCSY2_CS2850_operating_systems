//
// Created by Daniel Lucas on 15/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NEXTRA 5
#define MAXELEMENTS 15
#define LEFT 0
#define RIGHT 1
#define EMPTYSPACE -1

struct node {
    int v;
    struct node *next;
    struct node *prev;
};

struct list {
    struct node *head;  // points to the first node in the stack-like part of the list (node's previous member is always NULL)
    struct node *tail;  // points to the last node in the heap-like part of the list (node's next member is always NULL)
    struct node *left;  // points to the last integer stored in the stack-like part of the list
    struct node *right; // points the last integer stored in the heap-like part of the list
    int size;
};

void assignSpace(struct list *l);

void freeList(struct list *l);

void freeNode(struct node *n);

void freeSpace(struct list *l);

void printList(struct list *l);

void pull(struct list *l, int side);

void pullIntegers(struct list *l);

void push(struct list *l, int v);

void pushIntegers(struct list *l);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    srand(getchar()); // get char for random before any other prints

    struct list *l = malloc(sizeof(struct list)); // declare list
    printList(l); // check print doesn't error on empty

    l->head = malloc(sizeof(struct node)); // assign list
    l->head->v = 0;
    l->tail = malloc(sizeof(struct node));
    l->tail->v = 0;
    l->head->next = l->tail;
    printList(l);

    assignSpace(l);
    printList(l);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, (void *) pushIntegers, (struct list *) l);
    pthread_create(&t2, NULL, (void *) pullIntegers, (struct list *) l);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    freeList(l);
    return 0;
}

void assignSpace(struct list *l) {
    struct node *t = NULL;

    for (int i = 0; i < NEXTRA; i++) {
        t = malloc(sizeof(struct node));
        t->v = EMPTYSPACE;

        if (l->head == NULL) l->head = t;
        else {
            if (l->left == NULL) {
                l->head->next = t;
                t->prev = l->head;
            } else {
                l->left->next = t;
                t->prev = l->left;
            }
            l->left = t;
        }
    }

    if (l->right == NULL) {
        l->right = l->tail;
        l->left->next = l->right;
        l->right->prev = l->left;
    } else {
        l->left->next = l->right;
        l->right->prev = l->left;
    }

    l->left = l->head;
    while (l->left->next->v != EMPTYSPACE) l->left = l->left->next;
}

void freeList(struct list *l) {
    if (l != NULL) freeNode(l->head);
    free(l);
}

void freeNode(struct node *n) {
    if (n->next != NULL) freeNode(n->next);
    free(n);
}

void freeSpace(struct list *l) {
    int count = EMPTYSPACE;
    struct node *cur = l->left->next;
    while (cur->v == EMPTYSPACE) {
        cur = cur->next;
        count++;
    }

    if (count >= NEXTRA) {
        struct node *delStart = l->left;
        while (delStart->v != EMPTYSPACE) delStart = delStart->next;

        struct node *delEnd = delStart;
        for (int i = 0; i < (count - 1); i++) delEnd = delEnd->next;

        l->left->next = delEnd->next;
        delEnd->next = NULL;

        freeNode(delStart);
    }
}

void printList(struct list *l) {
    struct node *cur = NULL;

    pthread_mutex_lock(&mutex);
    if (l->head != NULL) {
        printf("[%d", l->head->v);

        cur = l->head->next;
        while (cur != NULL) {
            printf(", %d", cur->v);
            cur = cur->next;
        }

        printf("]\n");
    }
    pthread_mutex_unlock(&mutex);
}

void pull(struct list *l, int side) {
    pthread_mutex_lock(&mutex);
    if (l->left != l->head || l->right != l->tail) {
        if (side == LEFT) {
            if (l->left != l->head) {
                l->left = l->left->prev;
                l->left->next->v = EMPTYSPACE;
            } else pull(l, RIGHT);
        } else if (side == RIGHT) {
            if (l->right != l->tail) {
                l->right = l->right->next;
                l->right->prev->v = EMPTYSPACE;
            } else pull(l, LEFT);
        }
    } else printf("warning: no nodes to delete!\n");
    pthread_mutex_unlock(&mutex);

    freeSpace(l);
}

void pullIntegers(struct list *l) {
    int max = MAXELEMENTS;
    for (int i = 0; i < max; i++) {
        pull(l, rand() % 2);
        printList(l);
    }
}

void push(struct list *l, int v) {
    pthread_mutex_lock(&mutex);
    if (l->right->prev->v != EMPTYSPACE && l->left->next->v != EMPTYSPACE) assignSpace(l);

    if (v % 2 == 0) {
        l->right = l->right->prev;
        l->right->v = v;
    } else {
        l->left = l->left->next;
        l->left->v = v;
    }
    pthread_mutex_unlock(&mutex);
}

void pushIntegers(struct list *l) {
    int max = MAXELEMENTS;
    for (int i = 0; i < max; i++) {
        int z = 100 * ((float) rand()) / ((float) RAND_MAX);
        push(l, z);
        printList(l);
    }
}