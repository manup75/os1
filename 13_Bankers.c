#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int max[MAX_PROCESSES][MAX_RESOURCES];        // Maximum resource needs of each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Currently allocated resources to each process
int need[MAX_PROCESSES][MAX_RESOURCES];        // Remaining resources needed by each process
int available[MAX_RESOURCES];                  // Available resources
int numProcesses, numResources;

// Function to calculate the Need matrix
void calculateNeed() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int safeSeq[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    int count = 0;

    // Initialize Work and Finish
    for (int i = 0; i < numResources; i++)
        work[i] = available[i];

    for (int i = 0; i < numProcesses; i++)
        finish[i] = false;

    // Find a safe sequence
    while (count < numProcesses) {
        bool found = false;
        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < numResources; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == numResources) {
                    for (int k = 0; k < numResources; k++)
                        work[k] += allocation[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < numProcesses; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    // Input Maximum Resource Requirements as a matrix
    printf("Enter the Max matrix (%d x %d):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Allocation Resource Matrix as a matrix
    printf("Enter the Allocation matrix (%d x %d):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Available Resources as a single row
    printf("Enter the Available resources vector (%d):\n", numResources);
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the Need matrix
    calculateNeed();

    // Print Need matrix
    printf("Need matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Print Available Resources
    printf("Available Resources: ");
    for (int i = 0; i < numResources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    int safeSeq[MAX_PROCESSES]; // Array to store safe sequence

    // Check for safe state
    isSafe(safeSeq);

    return 0;
}

/*
5
3
7
5
3
3
2
2
9
0
2
4
2
2
5
3
3
0
1
0
2
0
0
3
0
2
2
1
1
0
0
2
3
3
2
*/

/*
Input: 
Enter the number of processes: 5
Enter the number of resources: 3
Enter the Max matrix (5 x 3):
7
5
3
3
2
2
9
0
2
4
2
2
5
3
3
Enter the Allocation matrix (5 x 3):
0
1
0
2
0
0
3
0
2
2
1
1
0
0
2
Enter the Available resources vector (3):
3
3
2

Output:
Need matrix:
7 4 3 
1 2 2 
6 0 0 
2 1 1 
5 3 1 
Available Resources: 3 3 2 
System is in a safe state.
Safe sequence is: P1 P3 P4 P0 P2

*/
