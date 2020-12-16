#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void sayHello(pid_t pid){
    printf("hello from process %d\n", getpid());
}
int main(){
    int *status;
    pid_t pid = fork();
    if (pid == 0){
        sayHello(pid);
        return 0;
    }
    pid = wait(NULL);
    printf("hello from process %d\n", pid);
    return 0;
}