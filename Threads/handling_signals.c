#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

void handle_sigtstp(int sig){
    printf("Stop not allowed\n");
}

void handle_sigcont(int sig){
    printf("Input number: ");
    fflush(stdout);
}

int main(int argc, char* agrv[]){
    signal(SIGCONT, &handle_sigcont);

    int x;
    printf("Input number: ");
    scanf("%d",&x);
    printf("Result %d * 5 = %d\n", x, x*5);

    return 0;
}