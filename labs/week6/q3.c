//
// Created by Daniel Lucas on 10/11/2020.
//

#include <stdlib.h>
#include <stdio.h>
struct node {
    char word[10];
    struct node *next;
};
int copyString(char *in, char *out){
    int i = 0;
    while (in[i] != '\0'){
        out[i] = in[i + 1];
        i++;
    }
    out[i]='\0';
    return i;
}
int main() {
    struct node *head = NULL;
    struct node *cur = NULL;
    char t[4][10];
    copyString("one", *(t + 3 ));
    copyString("Two", *(t + 2 ));
    copyString("and", *(t + 1 ));
    copyString("Three!", *(t + 0 ));
    for (int i=0; i<4; i++) {
        cur = malloc(sizeof(struct node));
        cur->next = head;
        copyString(t[i], cur->word);
        head = cur;
    }
    while ( head != NULL) {
        printf("%s ", head->word);
        cur = head;
        head = head->next;
        free(cur);
    }
}