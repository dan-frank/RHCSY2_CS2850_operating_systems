#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    pid_t pid = fork();
    if (pid){
        pid = fork();
    }
    if (pid == 0){
        printf("child\n");
    }
    else{
        printf("parent\n");
    }
    return 0;
}