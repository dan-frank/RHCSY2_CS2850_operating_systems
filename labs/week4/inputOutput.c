//
// Created by Daniel Lucas on 08/11/2020.
//

#include <unistd.h>
#include <fcntl.h>

#define PERMS 0666

int upper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c + 'A' - 'a';
    }

    return c;
}

int main(int argc, char *argv[]) {
//    creat(*(argv + 1), PERMS); // Creates file
//    creat(*(argv + 2), PERMS);

    char message[] = "File does not exist\n";
    int size = 20;
    char buf[size];

    int fdIn = open(*(argv + 1), O_RDONLY, 0); // Opens file and stores file ID
    int fdOut = open(*(argv + 2), O_WRONLY | O_TRUNC, 0);

    if (fdIn == -1 || fdOut == -1) { // Checks if file exists
        write(STDERR_FILENO, message, size);
    } else {
        int c;
        while ((c = read(fdIn, buf, size)) != '\0') { // Reads file in 20 char buffers
            for (int i = 0; i < c; i++) {
                buf[i] = upper(buf[i]);
            }
            write(fdOut, buf, c); // Writes to File
        }
    }

    close(fdIn);
    close(fdOut);
}