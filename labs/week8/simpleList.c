//
// Created by Daniel Lucas on 17/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
struct node {
    int length;
    char word[MAX];
    struct node *previous;
};

int stringLength(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

int copyString(char *in, char *out) {
    int i = 0;
    while (in[i] != '\0') {
        out[i] = in[i];
        i++;
    }
    out[i] = '\0';
    return i;
}

int getWord(char *buf, int *end, int maxLength) {
    int j = 0;
    char c;
    while (((c = getchar()) != ' ') && (j < maxLength) && (c != '\n')) {
        buf[j] = c;
        j++;
    }
    if (c == '\n') *end = 1;
    return j;
}

int countNodes(struct node *head) {
    int i = 0;
    struct node *iter = head;
    while (iter->previous) {
        i++;
        iter = iter->previous;
    }
    return i + 1;
}

void printNode(struct node *iter, int i) {
    printf("%d-th node:\n", i);
    printf("iter->word=%s(%d)\n", iter->word, iter->length);
    if (iter->previous)
        printf("iter->previous->word=%s(%d)\n",
               iter->previous->word,
               iter->previous->length);
}

int printList(struct node *head) {
    int i = countNodes(head);
    int j = 0;
    struct node *iter = head;
    while (iter->previous) {
        j++;
        printNode(iter, i--);
        iter = iter->previous;
    }
    j++;
    printNode(iter, i);
    return j;
}

void freeNode(struct node *cur, int *i) {
    printNode(cur, (*i)--);
    if (cur->previous) {
        freeNode(cur->previous, i);
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
    char buf[MAX];
    struct node *head = NULL;
    struct node *cur = NULL;
    int end = 0;
    int count = 0;
    printf("please enter some words:\n");
    while (end == 0) {
        int j = getWord(buf, &end, MAX);
        if (!j && !count && cur == NULL) return -1;
        if (j > 0) {
            buf[j] = '\0';
            cur = malloc(sizeof(struct node));
            cur->previous = head;
            copyString(buf, cur->word);
            cur->length = stringLength(buf);
            head = cur;
            count++;
        }
    }
    int iPrint = printList(head);
    int iFree = freeList(head);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n",
           count, iPrint, iFree);
    return 0;
}