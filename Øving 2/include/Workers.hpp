#ifndef WORKERS_HPP
#define WORKERS_HPP

#include <vector>
#include <thread>
#include <queue>
#include <mutex>

class Workers {
private:
    // Vector that holds all the worker threads
    std::vector<std::thread> threads;
    // Queue that holds the function pointers to different available jobs
    std::queue<std::function<void()>> jobs;
    // Mutex (lock stuff?)
    std::mutex mutex;
    // Condition variable (stuff??)
    std::condition_variable cv;
public:
    // Constructor. Specify a number of threads
    Workers(int numThreads);
    // Deconstructor
    ~Workers(); 
    // Pushing (posting) a job to jobs
    void post(void(*function)());
    // Used for joining all the threads
    void join();

};
#endif WORKERS_HPP