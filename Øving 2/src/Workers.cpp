#include "../include/Workers.hpp"

/**
 * Constructor for Workers.
 * Add a specified amount of thread´s to threads
*/
Workers::Workers(int numThreads) {
    for(int i = 0; i < numThreads; i++) {
        threads.push_back(std::thread(&Workers::job, this));
    }
}

Workers::~Workers() {
    join();
}

void Workers::join() {
    // The first thread to call join will have stop be false
    if(stop == true) {
        return;
    } else {
        // Set stop to true, because we are deconstructing and we do not
        // want the other threads to also join
        stop = true;

        // Wake up any threads that are still waiting to be woken up
        cv.notify_one();

        // Join on all threads
        for (auto& thread : threads) {
            thread.join();
        }
    }
}

void Workers::post(void(*job)()) {
    // Lock the mutex
    std::unique_lock<std::mutex> lock(mutex);

    // Push a job to jobs
    jobs.push(job);

    // Unlock the lock
    lock.unlock();

    // Wake up one thread that is waiting in job()
    cv.notify_one();
}

void Workers::post_timeout(void(*job)(), int waiting_time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(waiting_time));
    post(job);
}

void Workers::job() {
    while(!jobs.empty() || !stop) {
        std::unique_lock<std::mutex> lock(mutex);

        // Loop here while we are not supposed to stop and there is no job in jobs.
        // Use a condition variable for optimisation
        while (jobs.empty() && !stop) {
            cv.wait(lock);
        }

        // If there still are no jobs, but we are supposed to stop (we are finished)
        if (jobs.empty() && stop) {
            lock.unlock();
            cv.notify_one();
            break;
        }

        // If jobs is not empty, pluck a job from the queue
        if(!jobs.empty()) {
            // The job the thread will execute is the one at the front
            std::function<void()> job = jobs.front();

            // Remove the job from the queue
            jobs.pop();

            // Wake up the other threads that are waiting
            lock.unlock();
            cv.notify_one();

            // Execute the job (function)
            job();
        }
    }
}

