#include <stdio.h>
#include <stdlib.h>

int findNearest(int arr[], int n, int head) {
    int index = -1;
    int minDistance = 999999;

    for (int i = 0; i < n; i++) {
        if (arr[i] != -1 && abs(arr[i] - head) < minDistance) {
            minDistance = abs(arr[i] - head);
            index = i;
        }
    }
    return index;
}

void sstf(int requestQueue[], int n, int head) {
    int totalMovement = 0;
    int cumulativeSeek = 0;

    printf("SSTF Disk Scheduling Algorithm\n");
    printf("+------------------------+------------------+------------------+\n");
    printf("| Request                | Head Movement     | Cumulative Seek  |\n");
    printf("+------------------------+------------------+------------------+\n");

    for (int i = 0; i < n; i++) {
        int nearestIndex = findNearest(requestQueue, n, head);
        int movement = abs(requestQueue[nearestIndex] - head);
        totalMovement += movement;
        cumulativeSeek += movement;
        printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, requestQueue[nearestIndex], movement, cumulativeSeek);
        head = requestQueue[nearestIndex];
        requestQueue[nearestIndex] = -1; // Mark as processed
    }

    printf("+------------------------+------------------+------------------+\n");
    printf("Total Seek Time (SSTF): %d\n\n", totalMovement);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    sstf(requestQueue, n, head);
    return 0;
}
