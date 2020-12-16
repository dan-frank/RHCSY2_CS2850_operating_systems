#include <stdlib.h>
#include <stdio.h>

//this program define a linked list of integers, 
//prints the list content on the terminal and 
//free all nodes before terminating

struct node {
    int v;
    struct node *next;
};
int main(int argc, char *argv[]) {
    struct node *head = NULL,
                *cur = NULL;
    for (int i=1; i<=10; i++) {
        cur = malloc(sizeof(struct node));
        cur->next = head;
        cur->v = i;
        head = cur;
    }
    struct node *iter = head;
    while (iter != NULL) {
	    printf("Contents: %d\n", iter->v);
	    iter = iter->next;
    }
    while (head != NULL){
	    iter = (*head).next;
	    free(head);
	    head = iter;
    }
}


