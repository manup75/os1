#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4
#define NUM_THREADS 4

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

typedef struct {
    int row;
    int col;
} thread_data_t;

char operation;

void *add(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    C[data->row][data->col] = A[data->row][data->col] + B[data->row][data->col];
    pthread_exit(0);
}

void *subtract(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    C[data->row][data->col] = A[data->row][data->col] - B[data->row][data->col];
    pthread_exit(0);
}

void *multiply(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int sum = 0;
    for (int i = 0; i < MAX; i++) {
        sum += A[data->row][i] * B[i][data->col];
    }
    C[data->row][data->col] = sum;
    pthread_exit(0);
}

void *divide(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    if (B[data->row][data->col] != 0) {
        C[data->row][data->col] = A[data->row][data->col] / B[data->row][data->col];
    } else {
        C[data->row][data->col] = 0;
    }
    pthread_exit(0);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int thread_count = 0;

    printf("Enter elements of matrix A (4x4):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B (4x4):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    printf("Enter the operation to perform (+, -, *, /): ");
    scanf(" %c", &operation);

    void *(*operation_function)(void *);

    switch (operation) {
        case '+':
            operation_function = add;
            break;
        case '-':
            operation_function = subtract;
            break;
        case '*':
            operation_function = multiply;
            break;
        case '/':
            operation_function = divide;
            break;
        default:
            printf("Invalid operation.\n");
            return 1;
    }

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[thread_count].row = i;
            thread_data[thread_count].col = j;

            pthread_create(&threads[thread_count], NULL, operation_function, (void *)&thread_data[thread_count]);

            thread_count++;

            if (thread_count == NUM_THREADS) {
                for (int t = 0; t < NUM_THREADS; t++) {
                    pthread_join(threads[t], NULL);
                }
                thread_count = 0;
            }
        }
    }

    for (int t = 0; t < thread_count; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Result Matrix C:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
