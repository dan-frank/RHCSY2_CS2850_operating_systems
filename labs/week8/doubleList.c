//
// Created by Daniel Lucas on 17/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
struct node {
    int length;
    char word[MAX];
    struct node *next;
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
    char c = '\0';
    while (((c = getchar()) != ' ')
           && (c != '\n') && (j < maxLength)) {
        buf[j++] = c;
    }
    if (c == '\n') *end = 1;
    return j;
}

void printNode(struct node *iter, int i) {
    printf("%d-th node:\n", i);
    printf("iter->word=%s(%d)\n",
           iter->word, iter->length);
    if (iter->previous)
        printf("iter->previous->word=%s(%d)\n",
               iter->previous->word, iter->previous->length);
    if (iter->next)
        printf("iter->next->word=%s(%d)\n",
               iter->next->word, iter->next->length);

}

int printList(struct node *cur) {
    struct node *iter = cur;
    while (iter->previous != NULL) {
        iter = iter->previous;
    }
    int i = 0;
    while (iter->next != NULL) {
        i++;
        printNode(iter, i);
        iter = iter->next;
    }
    printNode(iter, ++i);
    return i;
}

void freeNode(struct node *cur, int *i) {
    (*i)++;
    if (cur->next) {
        struct node *temp = cur;
        printNode(cur, *i);
        freeNode(cur->next, i);
        free(temp);
    } else {
        printNode(cur, *i);
        free(cur);
    }
}

int freeList(struct node *cur) {
    struct node *iter = cur;
    while (iter->previous != NULL) {
        iter = iter->previous;
    }
    int i = 0;
    printf("free:\n");
    freeNode(iter, &i);
    return i;
}

int main() {
    char buf[MAX];
    struct node *head = NULL;
    struct node *cur = NULL;
    int end = 0;
    int count = 0;
    printf("enter words:\n");
    while (end == 0) {
        int j = getWord(buf, &end, MAX);
        // introduce a sanity check here to avoid errors for empy inputs
        if (j > 0) {
            buf[j] = '\0';
            cur = malloc(sizeof(struct node));
            cur->previous = head;
            copyString(buf, cur->word);
            cur->length = stringLength(buf);
            cur->next = NULL;
            if (count > 0) head->next = cur;
            head = cur;
            count++;
        }
    }
    cur->next = NULL;
    int iPrint = printList(cur);
    int iFree = freeList(cur);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint, iFree);
    return 0;
}