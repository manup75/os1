#include <stdio.h>
#include <stdlib.h>

void fcfs(int requestQueue[], int n, int head) {
    int totalMovement = 0;
    int cumulativeSeek = 0;

    printf("FCFS Disk Scheduling Algorithm\n");
    printf("+------------------------+------------------+------------------+\n");
    printf("| Request                | Head Movement     | Cumulative Seek  |\n");
    printf("+------------------------+------------------+------------------+\n");

    for (int i = 0; i < n; i++) {
        int movement = abs(requestQueue[i] - head);
        totalMovement += movement;
        cumulativeSeek += movement;
        printf("| %-22d -> %-6d | %-16d | %-16d |\n", head, requestQueue[i], movement, cumulativeSeek);
        head = requestQueue[i];
    }

    printf("+------------------------+------------------+------------------+\n");
    printf("Total Seek Time (FCFS): %d\n\n", totalMovement);
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

    fcfs(requestQueue, n, head);
    return 0;
}
