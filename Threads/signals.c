#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<signal.h>

int main(int argc, char* argv[]){
    
    pid_t pid = fork();

    if(pid==-1){
        return 1;
    }
    else if(pid==0){
        while(1){
            printf("Some text foes here. \n");
            usleep(50000);
        }
    }else{
        kill(pid,SIGSTOP);
        sleep(1);
        kill(pid,SIGCONT);
        sleep(2);
        kill(pid,SIGSTOP);
        kill(pid,SIGKILL);
        wait(NULL);
    }    
    
    return 0;
}