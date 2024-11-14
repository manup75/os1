#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createZombieProcess() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process
        printf("Parent process: Zombie process created. PID = %d\n", pid);  
    } 
    else {  // Child process
        printf("Child process exiting to become zombie.\n");
        exit(0);  
    }
}
void createOrphanProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }


    if (pid > 0) {  // Parent process
        printf("Parent process exiting to create orphan process.\n");
        exit(0);  
    } 
    else {  // Child process  
        printf("Child process (orphan) continuing after parent termination. PID = %d\n", getpid());
    }
}
void sumEvenOdd(int arr[], int size) {
    pid_t pid = fork();


    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) {  // Parent process
        int evenSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                evenSum += arr[i];
            }
        }
        printf("Parent process: Sum of even numbers = %d\n", evenSum);
        wait(NULL);  
    } 
    else {  // Child process
        int oddSum = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 != 0) {
                oddSum += arr[i];
            }
        }
        printf("Child process: Sum of odd numbers = %d\n", oddSum);
        exit(0);
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Calculating sum of even and odd numbers:\n");
    sumEvenOdd(arr, size);

    printf("\nCreating a zombie process:\n");
    createZombieProcess();  

    printf("\nCreating an orphan process:\n");
    createOrphanProcess();
    return 0;
}