#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>

void handle_sigusr1(int sig){
    printf("Multiplication is repetitive addition\n");
}

int main(int argc, char* argv[]){

    pid_t pid = fork();

    if(pid==-1){return 1;}
    else if(pid==0){
        //child process
        sleep(5);
        kill(getppid(),SIGUSR1);

    }else{
        struct sigaction sa = { 0 };
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);
        //parent process
        int x;
        printf("What is the result of 12*5? ");
        scanf("%d",&x);
        if(x==60){printf("Correct!\n");}
        else{printf("Incorrect!\n");}
        wait(NULL);
    }

    return 0;
}