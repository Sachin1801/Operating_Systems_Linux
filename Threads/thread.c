#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<wait.h>
#include<time.h>

int x =10;
void *routine1()
{
    x+=5;
    sleep(2);
    printf("Value of x: %d from process ID: %d and parent ID: %d\n",x,getpid(),getppid());
}

void *routine2(){
    sleep(2);
    printf("Value of x: %d from process ID: %d and parent ID: %d\n",x,getpid(),getppid());
}

int main(int argc, char *argv){
    
    pthread_t t1,t2; 
    if(pthread_create(&t1,NULL,&routine1,NULL)!=0){
        return 1;
    }
    if(pthread_create(&t2,NULL,&routine2,NULL)!=0){return 2;}
    if(pthread_join(t1, NULL)!=0){return 4;}
    if(pthread_join(t2,NULL)!=0){return 3;}

    
    return 0;
}