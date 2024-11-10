#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int primes[]={2,3,5,7,11,13,17,19,23,29};

// Function prototypes here
pthread_mutex_t mutex;
int globalsum=0;

void *routine(void *args){
    
    int idx = *(int*)args;
    int sum = 0;
    for(int i=0;i<5;++i){
        sum += primes[idx+i];
    }
    printf("Sum from thread %d: is %d\n",idx,sum);
    globalsum+=sum;
    free(args);
}

int main(int argc, char *argv[]) {
    // Your code here
    pthread_t th[2];
    // pthread_mutex_init(&mutex,NULL);
    int i;
    for( i=0;i<2;++i){
        pthread_mutex_lock(&mutex);
        int *a = malloc(sizeof(int));
        *a = i*5;
        if(pthread_create(&th[i],NULL,&routine,a)!=0){perror("Failed to create thread");}
        pthread_mutex_unlock(&mutex);
    }
    for(i=0;i<2;++i){
        if(pthread_join(th[i],NULL)!=0){perror("Failed to Join thread");}
    }
    // pthread_mutex_destroy(&mutex);
    printf("Global sum: %d\n",globalsum);

    return 0;
}
