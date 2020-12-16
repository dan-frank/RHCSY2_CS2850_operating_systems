//
// Created by Daniel Lucas on 10/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 500

struct node {
    int length;
    char word[MAXLENGTH];
    struct node *next;
};

/**
 * Calculates the length of a char array.
 *
 * @param s char array to calculate
 * @return int length of string array
 */
int stringLength(char *s) {
    int count = 0;

    while (1) {
        if (*(s + count) == '\0') {
            return count;
        }
        count++;
    }
}

/**
 * Reads a single word from input.
 *
 * @param buf char array to read from
 * @param end true/false for end of char array
 * @param maxLength max length of char array
 * @return length of word
 */
int getWord(char *buf, int *end, int maxLength) {
    int j = 0;
    char c;
    while (((c = getchar()) != ' ') && (c != '\n') && (j < maxLength)) {
        buf[j++] = c;
    }
    if (c == '\n') *end = 1;
    return j;
}

/**
 * Copy string from one char array to another.
 *
 * @param in char array to copy from
 * @param out char array to copy to
 * @return int size of copied string
 */
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
 * Prints words and list.
 *
 * @param head head of the list
 * @param nCount amount of words in list
 */
int printList(struct node *head, int nCount) {
    nCount--;
    int count = 0;
    struct node *iter = head;
    while (iter != NULL) {
        printf("%d-th word: %s (%d)\n", nCount + 1, iter->word, iter->length);
        iter = iter->next;
        nCount--;
        count++;
    }
    return count;
}

/**
 * Frees up resources from linked list.
 *
 * @return int amount of freed resources
 */
int freeList(struct node *head) {
    int count = 0;
    struct node *iter = head;
    while (head != NULL){
        iter = (*head).next;
        free(head);
        head = iter;
        count++;
    }
    return count;
}

int main() {
    char buf[MAXLENGTH];
    struct node *head = NULL, *cur = NULL, *prev = NULL;

    int end = 0;
    int count = 0;
    while (end != 1) {
        int j = getWord(buf, &end, MAXLENGTH);
        if (j > 0) {
            prev = head;
            buf[j] = '\0';
            cur = malloc((stringLength(buf) + 1) * sizeof(char));
            cur->length = stringLength(buf);
            copyString(buf, cur->word);
            cur->next = prev;
            head = cur;
            count = count + 1;
        }
    }
    int iPrint = printList(head, count);
    int iFree = freeList(head);
    printf("(count, iPrint, iFree)=(%d, %d, %d)\n", count, iPrint, iFree);
    return 0;
}