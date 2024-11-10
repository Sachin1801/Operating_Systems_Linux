#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[]){

    int arr[]={20,4,1,6,5,2,10};
    int n = sizeof(arr)/sizeof(int);
    int totalsum =0;
    int start, end;
    int fd[2];

    if(pipe(fd)==-1){
        printf("Pipe opening/creation failed \n");
        return 1;
    }
    pid_t pid = fork();

    if(pid==-1){
        printf("Forking failed\n");
        return 2;
    }else if(pid == 0){
        //child process 1
        start = 0;
        end = 1 * (n/3);
        close(fd[0]);
        int temp =0;
        for(int i=start;i<end;++i){
            temp += arr[i];
        }
        if(write(fd[1],&temp,sizeof(int))==-1){
            printf("Write failed in Child process with ID: %d, and Parent ID: %d", getpid(), getppid());
            return 3;
        }
        close(fd[1]);
        exit(0);
    }
    pid_t pid2 = fork();
    if(pid2 == -1){
        printf("Fork failed\n");
        return 2;
    }
    else if(pid2==0){
        //close the read end 
        close(fd[0]);
        start = 1*n/3;
        end = 2*n/3;
        int temp =0;
        for(int i=start;i<end;++i){
            temp += arr[i];
        }
        if(write(fd[1],&temp,sizeof(temp))==-1){
            printf("Write failed in Child 2\n");
            return 3;
        }
        close(fd[1]);
    }else{
        close(fd[1]);
        int sum1;
        int sum2;
        read(fd[0],&sum1,sizeof(int));
        read(fd[0],&sum2,sizeof(int));

        wait(NULL);
        wait(NULL);
        close(fd[0]);
        totalsum += sum1 + sum2;

        start = 2 * n/3;
        end = n;
        for(int i=start; i< end; ++i){
            totalsum+= arr[i];
        }

        

        printf("Total Sum: %d\n", totalsum);



    }

    return 0;
}