#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
    int arr[5];
    int fd = open("myfifo2", O_RDONLY);
    if(fd==-1){
        return 1;
    }
    int sum =0;
    for(int i=0;i<5;++i){
        if(read(fd,&arr[i],sizeof(int))==-1){
            return 3;
        }
        sum += arr[i];
        printf("Read %d from fifo file \n", arr[i]);
    }
    close(fd);

    fd = open("myfifo2",O_WRONLY);
    if(fd==-1){
        return 3;
    }

    if(write(fd,&sum,sizeof(int))==-1){
        return 2;
    }
    close(fd);

    return 0;
}