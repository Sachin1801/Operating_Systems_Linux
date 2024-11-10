#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include<time.h>

// Function prototypes here

void* rolldice(){
    int val = (rand()%6) +1;
    int *result = malloc(sizeof(int));
    *result = val;
    // printf("value: %d\n",val);
    return (void*) result;
}


int main(int argc, char *argv[]) {
    // Your code here
    int *res;
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th,NULL,&rolldice,NULL)!=0){
        return 1;
    }
    if(pthread_join(th,(void**) &res)!=0){return 2;}

    printf("value: %d\n", *res);
    free(res);

    
    return 0;
}
