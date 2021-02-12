#pragma once
#include <thread>
#include <queue>
#include <semaphore.h>

template <typename job, typename args>
class producer_consumer{
    public:
    std::queue<job> job_queue;
    //sem_t sem1;
};

struct turnstile_semaphore{
    turnstile_semaphore(int waits);
    int waits;
};

turnstile_semaphore::turnstile_semaphore(int waits){
    this -> waits = waits;
}