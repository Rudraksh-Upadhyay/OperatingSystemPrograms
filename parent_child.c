#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
    int pid;

    //create a new process
    pid = fork();

    if(pid == -1){
        printf("error occurred");
        exit(1);
    }

    if(pid != 0){
        //parent process
        printf("\nthis is parent process");
        printf("\nparent->%d", getpid());
    }

    else{
        //child process

        printf("\nthis is child process");
        printf("\nchild->%d",getpid());
    }

    return 0;
}