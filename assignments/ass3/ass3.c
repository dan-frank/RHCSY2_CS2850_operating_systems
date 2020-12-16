//
// Created by Daniel Lucas on 15/12/2020.
//

#include <stdio.h>
#include <stdlib.h>

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

void assignSpace(struct list *l, int nExtra);

void printList(struct list *l);

int main() {
    int nExtra = 5;
    struct list *l = malloc(sizeof(struct list));
    l->head = malloc(sizeof(struct node));
    l->head->v = 0;
    l->tail = malloc(sizeof(struct node));
    l->tail->v = 0;
    assignSpace(l, nExtra);
    printList(l);
    return 0;
}

void assignSpace(struct list *l, int nExtra) {
    for (int i = 0; i < nExtra; i++) {
        struct node *t = malloc(sizeof(struct node));
        t->v = -1;

        if (l->head == NULL) {
            l->head = t;
        } else {
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
}

void printList(struct list *l) {
    printf("[%d, ", l->head->v);

    struct node *cur = l->head->next;
    while (cur != NULL) {
        printf("%d, ", cur->v);
        cur = cur->next;
    }

    // print right


    printf("%d]\n", l->tail->v);
}