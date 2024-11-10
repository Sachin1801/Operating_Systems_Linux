#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

int main(int argc, char*argv[]){
    int x =10;
    pid_t pid = fork();
    if(pid==-1){return -1;}
    if(pid==0){
        x+=5;  
    }
    sleep(2);
    printf("Value of x: %d from process ID: %d and parent ID: %d\n",x,getpid(),getppid());
    if(pid>0){
        wait(NULL);
    }
    
    
    return 0;
}