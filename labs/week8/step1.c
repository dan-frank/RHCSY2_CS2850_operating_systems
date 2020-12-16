//
// Created by Daniel Lucas on 17/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

struct node {
    int v;
    struct node *next;
};

int countNodes(struct node *head) {
    int i = 0;
    struct node *iter = head;
    while (iter->next) {
        i++;
        iter = iter->next;
    }
    return i + 1;
}

void printNode(struct node *iter, int i) {
    printf("%d-th node:\n", i);
    printf("iter->int=%d\n", iter->v);
    if (iter->next)
        printf("iter->next->int=%d\n", iter->next->v);
}

int printList(struct node *head) {
    int i = countNodes(head);
    int j = 0;
    struct node *iter = head;
    while (iter->next) {
        j++;
        printNode(iter, i--);
        iter = iter->next;
    }
    j++;
    printNode(iter, i);
    return j;
}

void freeNode(struct node *cur, int *i) {
    printNode(cur, (*i)--);
    if (cur->next) {
        freeNode(cur->next, i);
        free(cur);
    } else {
        free(cur);
    }
}

int freeList(struct node *head) {
    int i = countNodes(head);
    int iStart = i;
    printf("free list:\n");
    freeNode(head, &i);
    i = iStart - i;
    return i;
}

int main() {
    struct node *head = NULL;
    struct node *cur = NULL;
    int count = 0;
    for (int i = 1; i < 10; i++) {
        cur = malloc(sizeof(struct node));
        cur->next = head;
        cur->v =  100 - i * 10;
        head = cur;
        count++;
    }
    int iPrint = printList(head);
    int iFree = freeList(head);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint, iFree);
    return 0;
}