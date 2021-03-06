#include <stdio.h>
#include <stdlib.h>
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
    srand(getchar()); // get char for random

    struct list *l = malloc(sizeof(struct list)); // declare list

    l->head = malloc(sizeof(struct node)); // assign list
    l->head->v = 0;
    l->head->prev = NULL;
    l->tail = malloc(sizeof(struct node));
    l->tail->v = 0;
    l->tail->next = NULL;
    l->head->next = l->tail;
    l->left = NULL;
    l->right = NULL;

    pthread_t t1, t2; // create and run threads
    pthread_create(&t1, NULL, (void *) pushIntegers, (struct list *) l);
    pthread_create(&t2, NULL, (void *) pullIntegers, (struct list *) l);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    freeList(l); // free list from memory

    return 0;
}

/**
 * Assigns free empty space in list.
 *
 * @param l list to add space too
 */
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

/**
 * Frees list from memory after freeing all nodes.
 *
 * @param l list to be freed from memory
 */
void freeList(struct list *l) {
    if (l != NULL) freeNode(l->head);
    free(l);
}

/**
 * Frees all linked nodes from memory.
 *
 * @param n node to start freeing from
 */
void freeNode(struct node *n) {
    if (n->next != NULL) freeNode(n->next);
    free(n);
}

/**
 * Removes assigned empty space from list.
 *
 * @param l list to remove empty space from
 */
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

/**
 * Prints all the nodes in the list.
 *
 * @param l list to print nodes from
 */
void printList(struct list *l) {
    struct node *cur = NULL;

    if (l->head != NULL) {
        printf("[%d", l->head->v);

        cur = l->head->next;
        while (cur != NULL) {
            printf(", %d", cur->v);
            cur = cur->next;
        }

        printf("]\n");
    }
}

/**
 * Removes top node from either the left or right side of the list
 *
 * @param l list to remove node from
 * @param side side to remove node from
 */
void pull(struct list *l, int side) {
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

    freeSpace(l);
}

/**
 * Attempts to pull node from list MAXELEMENTS times.
 *
 * @param l list to remove nodes from
 */
void pullIntegers(struct list *l) {
    int max = MAXELEMENTS;
    for (int i = 0; i < max; i++) {
        pthread_mutex_lock(&mutex);
        pull(l, rand() % 2);
        printList(l);
        pthread_mutex_unlock(&mutex);
    }
}

/**
 * Push node to left of list if odd and right of list if even.
 *
 * @param l list to push node to
 * @param v value to push to list
 */
void push(struct list *l, int v) {
    if (l->right == NULL && l->left == NULL) assignSpace(l);
    else if (l->right->prev->v != EMPTYSPACE && l->left->next->v != EMPTYSPACE) assignSpace(l);

    if (v % 2 == 0) {
        l->right = l->right->prev;
        l->right->v = v;
    } else {
        l->left = l->left->next;
        l->left->v = v;
    }
}

/**
 * Attempts to push node from list MAXELEMENTS times.
 *
 * @param l list to add nodes too
 */
void pushIntegers(struct list *l) {
    int max = MAXELEMENTS;
    for (int i = 0; i < max; i++) {
        int z = 100 * ((float) rand()) / ((float) RAND_MAX);
        pthread_mutex_lock(&mutex);
        push(l, z);
        printList(l);
        pthread_mutex_unlock(&mutex);
    }
}