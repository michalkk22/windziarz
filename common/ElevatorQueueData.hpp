#pragma once

#include <mutex>

#include "config.hpp"

struct ElevatorQueueData
{
    pthread_mutex_t mutex;   // access to data
    pthread_cond_t idleCond; // to wake up idle elevator

    unsigned int currentFloor;
    unsigned int queue[MAX_FLOOR];
    size_t size;
    unsigned int minFloor;
    unsigned int maxFloor;
};
