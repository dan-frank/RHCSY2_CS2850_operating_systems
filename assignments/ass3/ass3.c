//
// Created by Daniel Lucas on 15/12/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define NEXTRA 5
#define LEFT 0
#define RIGHT 1

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

void freeList(struct list *l);

void freeNode(struct node *n);

void freeSpace(struct list *l);

void printList(struct list *l);

void pull(struct list *l, int side);

void push(struct list *l, int v);

int main() {
    struct list *l = malloc(sizeof(struct list));

    printList(l);

    l->head = malloc(sizeof(struct node));
    l->head->v = 0;
    l->tail = malloc(sizeof(struct node));
    l->tail->v = 0;
    l->head->next = l->tail;

    printList(l);

    assignSpace(l, NEXTRA);
    printList(l);

    int test[6] = {12, 23, 34, 45, 56, 78};
    for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
        push(l, test[i]);
        printList(l);
    }

    for (int i = 0; i < (sizeof(test) / sizeof(test[0])) + 1; i++) {
        pull(l, LEFT);
        printList(l);
    }

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
        l->right = l->tail;
        l->left->next = l->right;
        l->right->prev = l->left;
    } else {
        l->left->next = l->right;
        l->right->prev = l->left;
    }

    l->left = l->head;
    while (l->left->next->v != -1) l->left = l->left->next;
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
    int count = -1;
    struct node *cur = l->left->next;
    while (cur->v == -1) {
        cur = cur->next;
        count++;
    }

    if (count >= NEXTRA) {
        struct node *delStart = l->left;
        while (delStart->v != -1) delStart = delStart->next;

        struct node *delEnd = delStart;
        for (int i = 0; i < (count - 1); i++) delEnd = delEnd->next;

        l->left->next = delEnd->next;
        delEnd->next = NULL;

        freeNode(delStart);
    }
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

void pull(struct list *l, int side) {
    if (l->left != l->head || l->right != l->tail) {
        if (side == LEFT) {
            if (l->left != l->head) {
                l->left = l->left->prev;
                l->left->next->v = -1;
                freeSpace(l);
            } else pull(l, RIGHT);
        } else if (side == RIGHT) {
            if (l->right != l->tail) {
                l->right = l->right->next;
                l->right->prev->v = -1;
                freeSpace(l);
            } else pull(l, LEFT);
        }
    } else {
        printf("warning: no nodes to delete!\n");
    }
}

void push(struct list *l, int v) {
    if (l->right->prev->v == -1 && l->left->next->v == -1) {
        if (v % 2 == 0) {
            l->right = l->right->prev;
            l->right->v = v;
        } else {
            l->left = l->left->next;
            l->left->v = v;
        }
    } else {
        assignSpace(l, NEXTRA);
        push(l, v);
    }
}