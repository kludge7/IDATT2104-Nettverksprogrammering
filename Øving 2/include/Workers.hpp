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
    // Mutex 
    std::mutex mutex;
    // Condition variable 
    std::condition_variable cv;
    // The function that is given to each thread, makes them run a task if possible
    void job();
    // Boolean to tell the threads to stop
    bool stop = false;
public:
    // Constructor. Specify a number of threads
    Workers(int numThreads);
    // Deconstructor
    ~Workers(); 
    // Pushing (posting) a job to jobs
    void post(void(*function)());
    // Used for joining all the threads
    void join();

    void post_timeout(void(*function)(), int waiting_time);
};
#endif // WORKERS_HPP