#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

// Semaphore for resource access
sem_t resource_sem;
// Semaphore to protect readers count
sem_t readers_count_sem;

int shared_resource = 0; // Shared resource
int read_count = 0; // Reader count

// Reader function
void reader(int reader_id) {
    while (true) {
        sem_wait(&readers_count_sem); // Lock the read count
        read_count++;
        if (read_count == 1) {
            sem_wait(&resource_sem); // First reader locks the resource
            std::cout << "Reader " << reader_id << " enters critical section.\n";
        }
        sem_post(&readers_count_sem); // Unlock the read count

        // Reading from shared resource
        std::cout << "Reader " << reader_id << " is reading the value " << shared_resource << std::endl;
        sleep(1); // Simulate reading time

        sem_wait(&readers_count_sem); // Lock the read count
        read_count--;
        if (read_count == 0) {
            std::cout << "Reader " << reader_id << " exits critical section.\n";
            sem_post(&resource_sem); // Last reader unlocks the resource
        }
        sem_post(&readers_count_sem); // Unlock the read count

        sleep(2); // Simulate time between reads
    }
}

// Writer function
void writer(int writer_id) {
    while (true) {
        sem_wait(&resource_sem); // Lock the resource for writing
        std::cout << "Writer " << writer_id << " enters critical section.\n";
        shared_resource++; // Writing to shared resource
        std::cout << "Writer " << writer_id << " wrote the value " << shared_resource << std::endl;
        sleep(2); // Simulate writing time
        std::cout << "Writer " << writer_id << " exits critical section.\n";
        sem_post(&resource_sem); // Unlock the resource

        sleep(3); // Simulate time between writes
    }
}

int main() {
    // Initialize semaphores
    sem_init(&resource_sem, 0, 1);
    sem_init(&readers_count_sem, 0, 1);

    // Create threads
    std::thread readers[3], writers[2];
    for (int i = 0; i < 3; ++i) {
        readers[i] = std::thread(reader, i);
    }
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer, i);
    }

    // Join threads
    for (int i = 0; i < 3; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    // Destroy semaphores
    sem_destroy(&resource_sem);
    sem_destroy(&readers_count_sem);

    return 0;
}
