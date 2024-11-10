#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[]){
    
    int fd[2]; 
    //fd[0] is the read end
    //fd[1] is the write end
    if(pipe(fd)==-1){
        fprintf(stderr,"Pipe creation failed or opening of pipe failed\n");
        return 1;
    }

    pid_t pid = fork();

    if(pid == 0 ){
        //child process
        close(fd[0]);
        int x;
        printf("Input a name: ");
        scanf("%d",&x);
        if(write(fd[1], &x, sizeof(int))==-1){
            printf("Error in writing to the pipe\n");
            return 2;
        }else{
            int s = write(fd[1], &x, sizeof(int));
            printf("return value of  write: %d\n",s);
        } //writing to the writing end
        close(fd[1]); // closing the read end
    }else{
        wait(NULL);
        close(fd[1]); // closing the write end as it is not needed
        int y ;
        if(read(fd[0], &y, sizeof(int))==-1){
            printf("Error in reading from the pipe\n");
            return 3;
        }else{
            int s = read(fd[0], &y, sizeof(int));
            printf("return value of  read: %d\n",s);
        } 
        close(fd[0]);
        printf("Got from the child process: %d\n", y);
    }
    
    return 0;
}