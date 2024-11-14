#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void cscan(int requestQueue[], int n, int head, int maxCylinder) {
    sort(requestQueue, n);
    int totalMovement = 0;
    int cumulativeSeek = 0;

    printf("C-SCAN Disk Scheduling Algorithm\n");
    printf("+------------------------+------------------+------------------+\n");
    printf("| Request                | Head Movement     | Cumulative Seek  |\n");
    printf("+------------------------+------------------+------------------+\n");

    // Move towards right first
    for (int i = 0; i < n; i++) {
        if (requestQueue[i] >= head) {
            int movement = abs(requestQueue[i] - head);
            totalMovement += movement;
            cumulativeSeek += movement;
            printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, requestQueue[i], movement, cumulativeSeek);
            head = requestQueue[i];
        }
    }

    // Move to max cylinder
    int movementToMax = abs(maxCylinder - head);
    totalMovement += movementToMax;
    cumulativeSeek += movementToMax;
    printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, maxCylinder, movementToMax, cumulativeSeek);

    // Jump to 0 and continue scanning
    int movementToZero = maxCylinder;
    totalMovement += movementToZero;
    cumulativeSeek += movementToZero;
    printf("| %-22d -> %-6d | %-16d | %-16d |\n", maxCylinder, 0, movementToZero, cumulativeSeek);

    head = 0;

    // Continue moving right again
    for (int i = 0; i < n; i++) {
        if (requestQueue[i] < head) {
            int movement = abs(requestQueue[i] - head);
            totalMovement += movement;
            cumulativeSeek += movement;
            printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, requestQueue[i], movement, cumulativeSeek);
            head = requestQueue[i];
        }
    }

    printf("+------------------------+------------------+------------------+\n");
    printf("Total Seek Time (C-SCAN): %d\n\n", totalMovement);
}

int main() {
    int n, head, maxCylinder;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the maximum cylinder number: ");
    scanf("%d", &maxCylinder);

    cscan(requestQueue, n, head, maxCylinder);
    return 0;
}
