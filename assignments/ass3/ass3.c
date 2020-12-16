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

int insertNode(struct node *head, int z, struct node **newHead) {
    int pos = 0;
    struct node *cur = head;
    while (cur != NULL) {
        head = cur;
        cur = cur->next;
        pos++;
    }
    struct node *new = malloc(sizeof(struct node));
    new->v = z;
    if (cur) new->next = NULL;
    if (cur != head) head-> next = new;
    else *newHead = new;
    new->next = cur;
    return pos;
}


int main() {
//    int nExtra = 5;
    struct node *head = NULL;

    struct node *t = malloc(sizeof(struct node));
    t->v = -1;
    t->next = NULL;
    t->prev = NULL;
    head = t;

//    for (int i = 0; i < nExtra; i++) {
//        insertNode(head, -1);
//    }

    printf("1:%d\n", head->v);
//    printf("2:%d\n", head->next->v);
//    printf("3:%d\n", head->next->next->v);
//    printf("4:%d\n", head->next->next->next->v);

    return 0;
}