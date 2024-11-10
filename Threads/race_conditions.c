#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<wait.h>
#include<time.h>

int mails=0;
pthread_mutex_t mutex;
void *routine1()
{
    for(int i=0;i<1000000;++i){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }   
}

int main(int argc, char *argv){
    
    pthread_t th[4]; 
    pthread_mutex_init(&mutex,NULL);
    for(int i=0;i<4;++i){
        if(pthread_create(&th[i],NULL,&routine1,NULL)!=0){
        return 1;
        }
        printf("Thread %d has started \n",i);
    }

    for(int i=0;i<4;++i){
        if(pthread_join(th[i], NULL)!=0){return 4;}
        printf("Thread %d has finished execution \n",i);
    }

    printf("Number of mails: %d\n",mails);

    pthread_mutex_destroy(&mutex);

    
    return 0;
}