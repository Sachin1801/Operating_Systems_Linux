#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int fuel=100;
pthread_mutex_t mutex;

// Function prototypes here
void* fuel_filler(){
    for(int i=0;i<5;++i){
        pthread_mutex_lock(&mutex);
        fuel+= 15;
        printf("Filled fuel.... %d\n",fuel);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    } 
}

void* car(){
    pthread_mutex_lock(&mutex);
    printf("here to get fuel\n");
    pthread_mutex_unlock(&mutex);


}

int main(int argc, char *argv[]) {
    // Your code here
    pthread_mutex_init(&mutex,NULL);
    pthread_t th[2];
    for(int i=0;i<2;++i){
        if(i==1){
            if(pthread_create(&th[1],NULL,&fuel_filler,NULL)!=0){return 1;}
        }else{
            if(pthread_create(&th[0],NULL,&car,NULL)!=0){return 1;}
        }
    }

    for(int i=0;i<2;++i){
            if(pthread_join(th[i],NULL)!=0){return 1;}
    }

    pthread_mutex_destroy(&mutex);

    
    return 0;
}
