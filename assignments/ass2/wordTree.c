//
// Created by Daniel Lucas on 02/12/2020.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXCHARS 100

struct node {
    char word[MAXCHARS];
    int length;
    int count;
    struct node *left;
    struct node *right;
};

int lowerCase(int *c) {
    if (*c >= 'a' && *c <= 'z') return 0;
    if (*c >= 'A' && *c <= 'Z') {
        *c = *c + 'a' - 'A';
        return 0;
    }
    *c = '\0';
    return -1;
}

int stringLength(char *s) {
    int i = 0;
    while (s[i] != '\0') i++;
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

/**
 * Compares alphabetical order of two char arrays.
 *
 * @param s1 char array to compare to
 * @param s2 char array to compare with
 * @return 0 if same word, - if a is before b, + if a is after b in the alphabet.
 */
int compareString(char *s1, char *s2) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void insertNode(struct node **t, char *s) {
    if (*t == NULL) {
        struct node *new = malloc(sizeof(struct node));
        copyString(s, new->word);
        new->count = 1;
        new->length = stringLength(s);
        new->left = NULL;
        new->right = NULL;
        *t = new;
    } else {
        int val = compareString((*t)->word, s);
        if (val > 0) insertNode(&(*t)->left, s);
        else if (val < 0) insertNode(&(*t)->right, s);
        else (*t)->count++;
    }
}

int getWordFromFile(char *buf, int *end, int maxLength) {
    int j = 0;
    char c;
    while (((c = getchar()) != ' ') && (c != '\n') && (c != EOF) && (j < maxLength)) {
        int ci = c;
        if (lowerCase(&ci) == 0) {
            buf[j] = ci;
            j++;
        }
    }
    if (c == EOF) *end = 1;
    buf[j] = '\0';
    return j;
}

void printNode(struct node *t) {
    if (t == NULL) return;
    if (t->left != NULL) printNode(t->left);
    printf(" %s(%d) ", t->word, t->count);
    if (t->right != NULL) printNode(t->right);
}

void freeNode(struct node *t) {
    if (t != NULL) {
        freeNode(t->left);
        freeNode(t->right);
        free(t);
    }
}

int main() {
    char buf[MAXCHARS];
    int end = 0;
    struct node *root = NULL;

    while (end == 0) {
        int j = getWordFromFile(buf, &end, MAXCHARS);
        if (j > 0) insertNode(&root, buf);
    }

    printNode(root);
    printf("\n");
    freeNode(root);
    return 0;
}