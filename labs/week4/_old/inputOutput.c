#include <unistd.h>
#include <fcntl.h>
#define PERMS 0666

int upper(int c) {
    if(c >= 'a' && c <= 'z'){
        return c + 'A' - 'a';
    }
    else {
        return c;
    }
}

int main(int argc, char **argv) {
    int size = 20;
    char message[] = "File does not exist\n";

    int fileIn = open(argv[1], O_WRONLY | O_TRUNC, PERMS);
    if (fileIn == -1) {
        write(STDOUT_FILENO, message, size);
    } else {
        char buffer[size];
        int c;
        while ((c = read(STDIN_FILENO, buffer, size)) != 0) {
            write(fileIn, buffer, c);
        }
    }
    close(fileIn);

    fileIn = open(argv[1], O_RDONLY, PERMS);
    int fileOut = open(argv[2], O_WRONLY | O_TRUNC, PERMS);
    if (fileOut == -1) {
        write(STDOUT_FILENO, message, size);
    } else {
        char buffer[size];
        int c;
        while ((c = read(fileIn, buffer, size)) != 0) {
            for (int i = 0; i < c; i++) {
                buffer[i] = upper(buffer[i]);
            }
            write(STDOUT_FILENO, buffer, c);
            write(fileOut, buffer, c);
        }
    }

    close(fileIn);
    close(fileOut);
}