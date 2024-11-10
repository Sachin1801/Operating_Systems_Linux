#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int primes[]={2,3,5,7,11,13,17,19,23,29};

// Function prototypes here
// pthread_mutex_t mutex;

void *routine(void *args){
    
    int idx = *(int*)args;
    int sum = 0;
    for(int i=0;i<5;++i){
        sum += primes[idx+i];
    }
    *(int*)args= sum;
    return args;
}

int main(int argc, char *argv[]) {
    // Your code here
    pthread_t th[2];
    // pthread_mutex_init(&mutex,NULL);
    int i;
    for( i=0;i<2;++i){
        int *a = malloc(sizeof(int));
        *a = i*5;
        // pthread_mutex_lock(&mutex);
        if(pthread_create(&th[i],NULL,&routine,a)!=0){perror("Failed to create thread");}
        // pthread_mutex_unlock(&mutex);
    }
    int globalsum=0;
    for(i=0;i<2;++i){
        int* totalsum;
        if(pthread_join(th[i],(void**)&totalsum)!=0){perror("Failed to Join thread");}
        globalsum += *totalsum;
        free(totalsum);
    }
    // pthread_mutex_destroy(&mutex);
    printf("Global sum: %d\n",globalsum);

    return 0;
}
