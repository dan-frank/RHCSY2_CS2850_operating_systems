//
// Created by Daniel Lucas on 17/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

struct treeNode {
    int val;
    struct treeNode *left;
    struct treeNode *right;
};

void insertNode(struct treeNode **t, int v) {
    if (*t == NULL) {
        *t = malloc(sizeof(struct treeNode));
        (*t)->val = v;
        (*t)->left = NULL;
        (*t)->right = NULL;
    } else {
        if (v < (*t)->val)
            insertNode(&((*t)->left), v);
        if (v > (*t)->val)
            insertNode(&((*t)->right), v);
        if (v == (*t)->val) {}
    }
}

void freeNode(struct treeNode **t) {
    if (*t != NULL) {
        freeNode(&((*t)->left));
        freeNode(&((*t)->right));
        free((*t));
    }
}

void printNode(struct treeNode *t) {
    if (t == NULL)
        return;

    if (t->left)
        printNode(t->left);

    if (!(t->val % 10))
        printf(" %d", t->val);
    else
        printf(" *%d", t->val);

    if (t->right)
        printNode(t->right);
}

int main() {
    struct treeNode *root = NULL;
    for (int i = 1; i < 10; i++) {
        insertNode(&root, (100 - i * 10));
    }

    srand(getchar());
    for (int i = 0; i < 10; i++) {
        int z = 100 * ((float)rand()) / ((float)RAND_MAX);
        insertNode(&root, z);
    }

    printf("[");
    printNode(root);
    printf(" ]\n");
    freeNode(&root);
    return 0;
}