#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXCHARS 100

int readMessage(int fd, char *reader);

int writeMessage(int fd, char *buf, char *author);

int compareString(char *s1, char *s2);

int copyString(char *in, char *out);

int stringLength(char *s);

int main() {
    int fd[2];
    int good = 0;
    int pid = 0;
    good = pipe(fd);
    if (good != 0) return -1;
    pid = fork();
    if (pid == 0) {
        close(fd[0]);
        char *author = "the child";
        writeMessage(fd[1], "hello", author);
        writeMessage(fd[1], "world", author);
        writeMessage(fd[1], "quit", author);
        close(fd[1]);
    } else {
        close(fd[1]);
        char *reader = "the parent";
        int end = 0;
        while (end == 0) {
            end = readMessage(fd[0], reader);
        }
        wait(NULL);
        printf("%s quits\n", reader);
        close(fd[0]);
    }
    return 0;
}

int writeMessage(int fd, char *buf, char *author) {
    int nbytes = stringLength(buf);
    printf("%s thinks ... \n", author);
    sleep(1);
    printf("%s writes \"%s\" (%d) to fd[1]=%d\n", author, buf, nbytes, fd);
    nbytes = write(fd, buf, nbytes + 1);
    return 0;
}

int readMessage(int fd, char *reader) {
    char buf[MAXCHARS];
    char c = ' ';
    int i = 0;
    while (c != '\0') {
        read(fd, &c, 1);
        buf[i++] = c;
    }
    buf[i] = '\0';
    if ((compareString(buf, "quit")) == 0) return -1;
    else {
        printf("%s reads \"%s\" (%d) from fd[0]=%d\n", reader, buf, stringLength(buf), fd);
        printf("%s waits ... \n", reader);
        sleep(1);
        return 0;
    }
}

int stringLength(char *s) {
    int i = 0;
    while (*(s + i) != '\0') {
        i++;
    }
    return i;
}

int copyString(char *in, char *out) {
    int i = 0;
    while (*(in + i) != '\0') {
        *(out + i) = *(in + i);
        i++;
    }
    *(out + i) = '\0';
    return i;
}

int compareString(char *s1, char *s2) {
    while (*(s1++) != '\0' && *(s2++) != '\0') {
        if (*s1 != *s2) return -1;
    }
    if (*s1 == *s2) return 0;
    else return -1;
}