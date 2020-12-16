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
    if (iter->v % 10 != 0)
        printf("*");
    printf("%d", iter->v);
    if (iter->next != NULL) {
        printf(", ");
    }
}

int printList(struct node *head) {
    int i = countNodes(head) + 1;
    int j = 0;
    struct node *iter = head;
    printf("[ ");
    while (iter->next) {
        j++;
        printNode(iter, i--);
        iter = iter->next;
    }
    j++;
    printNode(iter, i);
    printf(" ]\n");
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
    printf("free list:\n[ ");
    freeNode(head, &i);
    i = iStart - i;
    printf(" ]\n");
    return i;
}

int insertNode(struct node *head, int z) {
    int pos = 0;
    struct node *cur = head;
    while (z >= cur->v) {
        head = cur;
        cur = cur->next;
        pos++;
    }
    struct node *new = malloc(sizeof(struct node));
    new->v = z;
    head->next = new;
    new->next = cur;
    return pos;
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

    srand('d'); // getchar() instead of 'd'
    int z = 100 * ((float)rand()) / ((float)RAND_MAX);
    insertNode(head, z);

    int iPrint = printList(head);
    int iFree = freeList(head);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint, iFree);
    return 0;
}