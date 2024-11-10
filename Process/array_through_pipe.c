#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>

//2 processes
//child should henerate ranodm numberss and send them to the parent
//2) Parent is going to sum all the numbers and print the result


int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd)==-1){return 2;}
    pid_t pid = fork();
    if(pid == -1){return 1;}
    else if(pid==0){
        close(fd[0]);
        int arr[10];
        int n;
        srand(time(NULL));
        n = (rand() % 10)+1;
        printf("Generated: ");
        for(int i=0;i<n;++i){
            arr[i]= rand()%11;
            printf("%d ",arr[i]);
        }
        printf("\n");
        if(write(fd[1],&n,sizeof(int))==-1){return 4;}
        printf("Sent n = %d to parent\n",n);
        if(write(fd[1],arr, sizeof(int)*n)==-1){
            return 3;
        }
        printf("Sent array to parent\n");
        close(fd[1]);
    }
    else{
        //parent process
        
        close(fd[1]); // close the wirte end of the pipe
        int n;
        if(read(fd[0],&n,sizeof(int))==-1){return 5;}
        printf("Received n from child\n");
        int arr[11];
        if(read(fd[0],&arr,sizeof(int)*n)==-1){return 6;}
        printf("Received array from child\n");
        int sum=0;
        close(fd[0]);
        for(int i=0;i<n;++i){
            sum += arr[i];
        }
        printf("\nResult is %d. \n",sum);
        wait(NULL);
    }

}