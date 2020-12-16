#include <stdio.h>
#include <stdlib.h>

/**
 * Linked list node declared as struct for repeated use.
 */
struct node {
    int v;
    struct node *next;
};


// Declare methods to be used by main
void freeNode(struct node *cur, int *i);

void printNode(struct node *iter, int *i);

void insertNode(struct node **cur, int v);

/**
 * Main method, called when run.
 *
 * @return 0 if successful
 */
int main() {
    struct node *head = NULL; // Declares head node
    int count = 0; // Counts inserted nodes
    srand(getchar()); // Generates random serial based on user string
    for (int i = 0; i < 50; i++) { // repeats following code 50 times (attempts to insert 50 nodes)
        int z = 100 * ((float) rand()) / ((float) RAND_MAX); // Value to be inserted
        insertNode(&head, z); // Insert node into list
        count++; // counts inserted nodes
    }
    struct node *tail = head; // sets tail to head to make list circular
    while (tail->next != head) tail = tail->next; // searches for head to set tail
    tail->next = NULL; // null terminates/unbinds the tail so it can be printed
    int iPrint = 0; // print counter
    int iFree = 0; // free counter
    printNode(head, &iPrint); // prints all nodes in list
    freeNode(head, &iFree); // frees all nodes from memory
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint,
           iFree); // prints counters (checks all nodes have been printed and freed)
    return 0;
}

/**
 * Prints single node. Is called recursively to print list.
 *
 * @param iter node to print
 * @param i print counter pointer
 */
void printNode(struct node *iter, int *i) {
    if (*i == 0) printf("["); // Prints first bracket
    if (iter) { // checks node exists
        if (iter->next) printf("%d, ", iter->v); // if next print next node value
        else printf("%d]\n", iter->v); // if no next node print current value and close printed bracket
        (*i)++; // update counter
        printNode(iter->next, i); // print next node
    }
}

/**
 * Frees single node. Is called recursively to print list.
 *
 * @param iter node to print
 * @param i free counter pointer
 */
void freeNode(struct node *iter, int *i) {
    if (*i == 0) printf("free:\n["); // Prints first bracket
    if (iter) {
        if (iter->next) printf("%d, ", iter->v); // if next print next node value
        else printf("%d]\n", iter->v); // if no next node print current value
        (*i)++; // update counter
        if (iter->next) freeNode(iter->next, i); // checks if next node exists and then calls free node
        free(iter); // frees current node
    }
}

/**
 * Inserts node into List.
 *
 * @param cur Current node
 * @param i value to insert
 */
void insertNode(struct node **cur, int i) {
    if (*cur == NULL || i < (*cur)->v) { // checks if node exists and if current value is less than current value
        struct node *temp = malloc(sizeof(struct node)); // creates new space in memory for node
        temp->v = i; // sets new node value to i
        if (*cur == NULL) temp->next = temp; //
        else { // called current node exists
            temp->next = *cur; // sets new node->next to current
            struct node *tail = *cur; //
            while (tail->next != *cur) tail = tail->next; //
            tail->next = temp; //
        }
        *cur = temp; // sets current node to temp node
    } else { // called if node exists and
        if ((*cur)->next->v <= (*cur)->v) {
            struct node *temp = malloc(sizeof(struct node));
            temp->v = i;
            temp->next = (*cur)->next; // new node->next is set to current node->next
            (*cur)->next = temp; // current node-> next is set to new node
        } else {
            if ((*cur)->v != i) insertNode(&(*cur)->next, i);
        }
    }
}


/*
 * Question 1.3
 *
 * 1. Why is count greater than the number of printed and freed node? Does this mean that the program is not
 *    freeing all nodes?
 * Count is a counter for all nodes inserted into the list but because there can be duplicate elements which don't get
 * added to the list then the actual length of the list is the print counter.
 *
 * 2. Consider the implementation of insertNode. In what particular case is `*cur == NULL` true? and when is
 *    `(*cur)->next->v <= (*cur)->v` is true?
 * *cur == NULL is true when the current node is empty.
 * (*cur)->next->v <= (*cur)->v is true when the next nodes value is equal to or less than the current node.
 *
 * 3. What happens when you try to insert a value that is already in the list? Why, in this case, is the proposed
 *    solution more convenient than the one presented in Section 1 of Exercise lab-sheet 8 ?
 *
 *
 * 4. Why do you need a pointer to a pointer to an object of type struct node when you call insertNode?
 * It allows you to chang the head pointer directly instead of returning the new one.
 *
 * 5. What is the role of the instructions on line 23 and 24? How does the instruction on line 24 simplify the
 *    implementation of printNode and freeNode?
 * Line 23
 * Line 24 breaks the loop in the circular linked list, that way both printNode and freeNode can check for NULL
 * instead of passing head through each call and comparing with head to find the end of the list.
 *
 * 6. Why should you pass a pointer to a int to printNode and freeNode?
 * To save memory so an int doesn't have to be allocated for each run of the recursive loop.
 */