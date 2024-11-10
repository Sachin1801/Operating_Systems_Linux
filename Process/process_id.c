#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>  // for strerror()

/**
 * Checks for errors after calling wait() and prints detailed error information.
 * 
 * This function attempts to wait for any child process to terminate. If wait() 
 * returns -1, it indicates an error, and the function retrieves the global 
 * errno value to determine the specific error. It prints the error number, 
 * corresponding error message, and a description of the error based on the 
 * errno value. Specifically, it handles the cases where there are no child 
 * processes (ECHILD) and when the wait is interrupted by a signal (EINTR). 
 * If wait() succeeds, the process ID of the terminated child is printed.
 */
void check_wait_error() {
    pid_t wait_result = wait(NULL);
    if(wait_result == -1) {
        // Save errno immediately as other functions might change it
        int error_number = errno;
        
        printf("wait() returned -1\n");
        printf("errno value: %d\n", error_number);
        printf("Error message: %s\n", strerror(error_number));
        
        switch(error_number) {
            case ECHILD:
                printf("No child processes (ECHILD)\n");
                break;
            case EINTR:
                printf("Interrupted by signal (EINTR)\n");
                break;
            default:
                printf("Unknown error\n");
        }
    } else {
        printf("wait() succeeded, returned: %d\n", wait_result);
    }
}

int main() {
    printf("Testing wait with no children:\n");
    check_wait_error();  // Will set errno to ECHILD
    
    printf("\nTesting wait with child:\n");
    pid_t id = fork();
    
    if(id == 0) {  // Child
        printf("Child pricess id: %d\n",getpid());
        exit(0);
    } else {  // Parent
        check_wait_error();  // Will succeed
        check_wait_error();  // Will set errno to ECHILD again
    }
    
    return 0;
}