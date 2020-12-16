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

void pull(struct list *l);

void push(struct list *l, int v);

void freeList(struct list *l);

void freeNode(struct node *n);

int main() {
    int nExtra = 5;
    struct list *l = malloc(sizeof(struct list));

    printList(l);

    l->head = malloc(sizeof(struct node));
    l->head->v = 0;
    l->tail = malloc(sizeof(struct node));
    l->tail->v = 0;
    l->head->next = l->tail;

    printList(l);
    assignSpace(l, nExtra);
    printList(l);

    freeList(l);

    return 0;
}

void assignSpace(struct list *l, int nExtra) {
    struct node *t = NULL;

    for (int i = 0; i < nExtra; i++) {
        t = malloc(sizeof(struct node));
        t->v = -1;

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
        l->right = l->left;
        l->left = l->left->prev;
        l->right->next = l->tail;
    } else l->left->next = l->right;
}

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

void pull(struct list *l);

void push(struct list *l, int v);

void freeList(struct list *l) {
    if (l != NULL) freeNode(l->head);
    free(l);
}

void freeNode(struct node *n) {
    if (n->next != NULL) freeNode(n->next);
    free(n);
}