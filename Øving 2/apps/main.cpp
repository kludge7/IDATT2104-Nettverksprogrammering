#include "../include/Workers.hpp"
#include <iostream>
#include <chrono>

void thread_job(int thread_id) {
    printf("Thread %d started\n", thread_id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("Thread %d halfway\n", thread_id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("Thread %d ended\n", thread_id);
}

int main() {
    // Create a Workers object with 2 worker threads
    Workers worker_threads(4);
    Workers event_loop(1);

    worker_threads.post([] {
    thread_job(1);
    });
    worker_threads.post([] {
    thread_job(2);
    });
    event_loop.post([] {
    thread_job(3);
    });
    event_loop.post([] {
    thread_job(4);
    });

    return 0;
}
