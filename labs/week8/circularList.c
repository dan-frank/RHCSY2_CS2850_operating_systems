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
    while (head) {
        i++;
        head = head->previous;
    }
    return i;
}

void printNode(struct node *iter, int i) {
    printf("%d-th node:\n", i);
    printf("iter->word=%s(%d)\n", iter->word, iter->length);
    if (iter->previous)
        printf("iter->previous->word=%s(%d)\n",
               iter->previous->word, iter->previous->length);
}

int printList(struct node *tail) {
    int i = 0;
    struct node *iter = tail;
    struct node *start = tail;
    printNode(iter, ++i);
    while (iter != tail->previous) {
        start = iter;
        while (iter->previous != start) {
            iter = iter->previous;
        }
        printNode(iter, ++i);
    }
    return i;
}

void freeNode(struct node *cur, int *i) {
    if (cur != NULL) {
        printNode(cur, (*i)--);
        freeNode(cur->previous, i);
        free(cur);
    }
}

int freeList(struct node *cur) {
    int i = countNodes(cur);
    int iStart = i;
    printf("free %d nodes:\n", i);
    freeNode(cur, &i);
    return iStart - i;
}

int main() {
    char buf[MAX];
    struct node *head = NULL;
    struct node *cur = NULL;
    struct node *tail = NULL;
    int end = 0;
    int count = 0;
    printf("enter words:\n");
    while (end == 0) {
        int j = getWord(buf, &end, MAX);
        // introduce a sanity check here to avoid errors for empy inputs
        if (j > 0) {
            buf[j] = '\0';
            cur = malloc(sizeof(struct node));
            if (count == 0) tail = cur;
            cur->previous = head;
            copyString(buf, cur->word);
            cur->length = stringLength(buf);
            head = cur;
            count++;
        }
    }
    tail->previous = head;
    int iPrint = printList(tail);
    tail->previous = NULL;
    int iFree = freeList(head);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint, iFree);
    return 0;
}