#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int hmm(){
    pid_t pid = 1;
    if ((pid = fork())){
        pid = fork();
        return 1;
    }
    wait(NULL);
    return 0;
}
int main() {
    printf("%d\n", hmm());
    return 0;
}