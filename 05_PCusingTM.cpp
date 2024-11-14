#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

const int MAX_QUEUE_SIZE = 5;
std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cond_empty; // Condition variable for empty buffer
std::condition_variable cond_full;  // Condition variable for full buffer

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        std::unique_lock<std::mutex> lock(mtx);
        
        cond_empty.wait(lock, [] { return buffer.size() < MAX_QUEUE_SIZE; }); // Wait if buffer is full
        
        std::cout << "Producer " << id << " is entering critical section." << std::endl;
        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;
        std::cout << "Producer " << id << " has exited critical section." << std::endl;
        
        lock.unlock();
        cond_full.notify_one(); // Notify one consumer
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simulate work
        std::unique_lock<std::mutex> lock(mtx);
        
        cond_full.wait(lock, [] { return !buffer.empty(); }); // Wait if buffer is empty
        
        std::cout << "Consumer " << id << " is entering critical section." << std::endl;
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        std::cout << "Consumer " << id << " has exited critical section." << std::endl;
        
        lock.unlock();
        cond_empty.notify_one(); // Notify one producer
    }
}

int main() {
    std::thread producers[2], consumers[2];
    for (int i = 0; i < 2; ++i) {
        producers[i] = std::thread(producer, i);
        consumers[i] = std::thread(consumer, i);
    }

    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
