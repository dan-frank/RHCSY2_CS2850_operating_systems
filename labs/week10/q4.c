//
// Created by Daniel Lucas on 08/12/2020.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int forkingHell();
int forkingQuiz();

int main(){
    printf("%d\n", forkingQuiz());
}

int forkingHell() {
    int pid = fork();
    if (!pid){
        pid = fork();
        pid = fork();
        if (!pid){
            return 1;
        }
        return 2;
    }
    wait(NULL);
    return 0;
}

int forkingQuiz() {
    int pid = fork();
    fork();
    if (!pid){
        pid = fork();
        pid = fork();
        if (!pid) return 0;
        return 0;
    }
    wait(NULL);
    return 0;
}