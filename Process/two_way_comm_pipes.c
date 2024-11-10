#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>

int main(int argc ,char* argv[]){
    // 1st process gets input n 
    //1st process writes number to pipe and sends to other process
    //2nd process reads that number and perform n *=4
    //return value to parent process

    int fd[2];

    if(pipe(fd)==-1){ //failed making pipe
        return 1;
    }
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    // close(fd[0]);
    if(write(fd[1],&n,sizeof(int))==-1){
        return 3;
    }
    // close(fd[1]);
    pid_t pid = fork();
    if(pid == -1){   return 2; }
    else if(pid==0){
        //child process
        //read n from pipe and multiply with 4
        //write back to the same pipe
        // close(fd[1]);
        int temp;
        if(read(fd[0],&temp,sizeof(int))==-1){ return 4;}
        printf("Read successfully from pipe to get n\n");
        close(fd[0]);
        temp *=4;
        if(write(fd[1],&temp,sizeof(int))==-1){ return 3;}
        printf("Written successfully from pipe to get n\n");
        close(fd[1]);
    }else{
        wait(NULL);
        close(fd[1]);
        if(read(fd[0],&n,sizeof(int))==-1){return 4;}
        printf("Read successfully from pipe to get new value of n\n");
        close(fd[0]);
        printf("New output: %d\n",n);
    }

    return 0;
}