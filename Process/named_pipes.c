#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> // this is for pid_t
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>

int main(int argc, char* argv[]){

    if(mkfifo("myfifo1", 0777)==-1){ //0777 is a access permission mode, which means anyone can read/write to the file
        if(errno != EEXIST){
            printf("failed to create fifo file \n");
            exit(1);
        }
    } 
    printf("Opening....\n");
    int fd = open("myfifo1", O_RDWR); // in this case we would only get 1 because we are only opening the file for writing
    printf("Opened\n");
    int x = 'Z';
    if(write(fd,&x,sizeof(int))==-1){
        printf("Failed to write in the mkfifo file \n");
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}