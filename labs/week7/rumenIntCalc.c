#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAXNUMBERS 10
#define MAXCHARS 100

int readLine(char *s, int max) {
    char c;
    char cOld = ' ';
    int i = 0;
    while ((c = getchar()) != '\n') {
        if (c != ' ' || cOld != ' ') {
            *s = c;
            s++;
            i++;
        }
        cOld = c;
    }
    if (*(s - 1) == ' ') {
        s--;
        i--;
    }
    *s = '\0';
    return i;
}

int getInt(char *s, int *n, int *pos) {
    char c;
    *n = 0;
    s = s + *pos;
    while ((c = *s) != ' ' && c != '\0') {
        if (c <= '9' && c >= '0') {
            *n = *n * 10 + c - '0';
        }
        s++;
        (*pos)++;
    }
    s++;
    (*pos)++;
    if (c == '\0') return 1;
    else return 0;
}

int getIntegers(int *v, char *s, int MAX) {
    int j = 0;
    int stop = 0;
    int n;
    int pos = 0;
    while (stop != 1 && j < MAX) {
        stop = getInt(s, &n, &pos);
        v[j++] = n;
    }
    return j;
}

void executeCommand(int *v, char op,int len) {
    int res=v[0];
    if (op == '+') {
        printf("%d  + ",v[0]);
        for (int i = 1; i < len-1; ++i) {
            printf("%d  + ",v[i]);
            res= res+v[i];

        }
        res=res+v[len-1];
        printf("%d = %d\n",v[len-1],res);
    }
    if (op == '-') {
        printf("%d  - ",v[0]);
        for (int i = 1; i < len-1; ++i) {
            printf("%d  - ",v[i]);
            res= res-v[i];

        }
        res=res-v[len-1];
        printf("%d = %d\n",v[len-1],res);
    }
    if (op == '*') {
        printf("%d  * ",v[0]);
        for (int i = 1; i < len-1; ++i) {
            printf("%d  * ",v[i]);
            res= res*v[i];

        }
        res=res*v[len-1];
        printf("%d = %d\n",v[len-1],res);
    }
    if (op == '/') {
        printf("%d  / ",v[0]);
        for (int i = 1; i < len-1; ++i) {
            printf("%d  / ",v[i]);
            res= res/v[i];

        }
        res=res/v[len-1];
        printf("%d = %d\n",v[len-1],res);
    }
    if (op == '%') {
        printf("%d  %c ",v[0],op);
        for (int i = 1; i < len-1; ++i) {
            printf("%d  %c ",v[i],op);
            res= res%v[i];

        }
        res=res%v[len-1];
        printf("%d = %d\n",v[len-1],res);
    }
}

int main() {
    char s[MAXCHARS];
    int v[MAXNUMBERS];
    //+, -, *, %/
    char op = '+';
    while (1) {
        printf("write quit to exit or enter two integers (%c): ", op);
        int len = readLine(s, MAXCHARS);
        if (!strcmp(s, "quit")) return 0;
        if (len == 1) op = *s;
        else {
            if (fork() == 0) {
                int c =  getIntegers(v, s, MAXNUMBERS);
                printf("(n1, n2)=(%d, %d) \n", v[0], v[1]);
                executeCommand(v, op,c);

                return 0;
            }
            wait(NULL);
            op='+';
        }

    }
}