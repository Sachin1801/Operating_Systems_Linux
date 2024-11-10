#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h> //linux specific library
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
    if(argc !=2){
        fprintf(stderr,"Usage: %s \n",argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    pid_t id = fork();

    if(id ==-1){
        printf("Fork failed \n");
        exit(1);
    }
    else if(id==0){
        //child process
        for(int i=1;i<=n/2;++i){
            printf("%d, ",i);
            fflush(stdout);
        }
        printf("Printed by Child Process \n");
    }else{
        wait(NULL); // waiting for child process to complete first
        for(int i=(n/2)+1;i<=n;++i){
            printf("%d, ",i);
            fflush(stdout);
        }
        printf("Printed by Parent Process.\n");
    }
    return 0;
}