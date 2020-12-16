#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int MAX = 20;
    char s[MAX];
    char *argv[4];
    argv[0] = "select.sh";
    argv[3] = NULL;
    while (1) {
        printf("enter ID range or quit to exit: ");
        readLine(s, MAX);
        if (strcmp(s, "quit")) {
            separateInputs(s, argv);
            if (!fork()) {
                executeCommang(argv);
            }
            wait(NULL);
        }
        else {
            return 0;
        }
    }
}
