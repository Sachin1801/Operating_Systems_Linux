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
    srand(time(NULL));
    int i;
    for(int i=0;i<5;i++){
        arr[i] = rand() %100;
    }

    int fd = open("myfifo2", O_WRONLY);
    if(fd==-1){
        printf("error in fifo open");
        return 1;
    }
    if(write(fd,arr,sizeof(int)*5)==-1){
        return 2;
    }
    printf("Generated 5 random numbers\n");
    close(fd);

    fd = open("myfifo2", O_RDONLY);
    if(fd==-1){
        printf("Unable to read\n");
        return 2;
    }
    int sum ;
    if(read(fd,&sum,sizeof(int))==-1){
        printf("read failed from mkfifo in m_comm1");
        return 3;
    }
    close(fd);

    printf("Sum is %d\n",sum);


    return 0;
}