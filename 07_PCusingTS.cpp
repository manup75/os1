#include <iostream>
#include <thread>
#include <semaphore.h>
#include <queue>
#include <chrono>
#include <mutex>

const int MAX_QUEUE_SIZE = 5;
std::queue<int> buffer;
sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
std::mutex mtx;

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        sem_wait(&empty); // Decrease empty slots
        
        std::cout << "Producer " << id << " is entering critical section." << std::endl;
        mtx.lock(); // Lock the buffer (critical section)
        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;
        mtx.unlock(); // Unlock the buffer
        std::cout << "Producer " << id << " has exited critical section." << std::endl;

        sem_post(&full); // Increase full slots
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simulate work
        sem_wait(&full); // Decrease full slots
        
        std::cout << "Consumer " << id << " is entering critical section." << std::endl;
        mtx.lock(); // Lock the buffer (critical section)
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        mtx.unlock(); // Unlock the buffer
        std::cout << "Consumer " << id << " has exited critical section." << std::endl;

        sem_post(&empty); // Increase empty slots
    }
}

int main() {
    sem_init(&empty, 0, MAX_QUEUE_SIZE); // Initialize empty slots
    sem_init(&full, 0, 0); // Initialize full slots

    std::thread producers[2], consumers[2];
    for (int i = 0; i < 2; ++i) {
        producers[i] = std::thread(producer, i);
        consumers[i] = std::thread(consumer, i);
    }

    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
