#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

std::mutex resource_mutex;
std::mutex readers_count_mutex;

int shared_resource = 0; // Shared resource
int read_count = 0; // Reader count

// Reader function
void reader(int reader_id) {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(readers_count_mutex);
            read_count++;
            if (read_count == 1) {
                resource_mutex.lock(); // First reader locks the resource
                std::cout << "Reader " << reader_id << " enters critical section.\n";
            }
        }

        // Reading from shared resource
        std::cout << "Reader " << reader_id << " is reading the value " << shared_resource << std::endl;
        sleep(1); // Simulate reading time

        {
            std::unique_lock<std::mutex> lock(readers_count_mutex);
            read_count--;
            if (read_count == 0) {
                std::cout << "Reader " << reader_id << " exits critical section.\n";
                resource_mutex.unlock(); // Last reader unlocks the resource
            }
        }

        sleep(2); // Simulate time between reads
    }
}

// Writer function
void writer(int writer_id) {
    while (true) {
        std::unique_lock<std::mutex> lock(resource_mutex); // Lock the resource for writing
        std::cout << "Writer " << writer_id << " enters critical section.\n";
        shared_resource++; // Writing to shared resource
        std::cout << "Writer " << writer_id << " wrote the value " << shared_resource << std::endl;
        sleep(2); // Simulate writing time
        std::cout << "Writer " << writer_id << " exits critical section.\n";
        sleep(3); // Simulate time between writes
    }
}

int main() {
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

    return 0;
}
