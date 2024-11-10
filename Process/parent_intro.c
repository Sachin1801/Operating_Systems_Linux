#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid;
    int status;

    //fork a child process
    pid = fork();
    if(pid<0){ //error occured
        fprintf(stderr,"Fork failed\n");
        return 1;
    }else if(pid==0){
        //child process
        execlp("ls","ls",NULL);
        printf("Child process PID: %d\n",pid);
    }else{
        //parent process
        printf("Parent process PID: %d\n",pid);
        pid = wait(&status);
        printf("Child process PID = %d\n",pid);
        printf("Child process completed\n");
    }
    return 0;
}