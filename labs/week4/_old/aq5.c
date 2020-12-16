#include <stdio.h>
int main(){
    char c;
    int MAX = 15;
    char vs[MAX];
    char *s = "one two three four five";
    int i = 0;
    printf(">");
    while (((c = getchar()) != '\n') && (i < MAX)){
        *(vs + i) = c;
        s++; ->s;
        i++;
    }
    vs[i] = '\0';
    printf("vs = %s\n", vs);
    printf("s = %s\n", s + 1);
}