#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 3
#define MAX_MEALS 1 // Number of times each philosopher will eat

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t lock;
int meal_count[NUM_PHILOSOPHERS] = {0}; // Tracks meals for each philosopher

void *philosopher(void *arg)
{
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (meal_count[id] < MAX_MEALS)
    {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Picking up forks
        pthread_mutex_lock(&lock);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_unlock(&lock);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(2); // Eating time
        meal_count[id]++;
        printf("Philosopher %d finished eating (%d/%d times).\n", id, meal_count[id], MAX_MEALS);

        // Putting down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }

    printf("Philosopher %d is done eating and leaving.\n", id);
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores and mutex
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    pthread_mutex_init(&lock, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosophers to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&lock);

    printf("All philosophers have finished eating.\n");
    return 0;
}
