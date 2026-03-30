#pragma once

#include <array>
#include <mutex>

#include "config.hpp"

struct ElevatorQueueData
{
    pthread_mutex_t mutex;
    unsigned int currentFloor;
    std::array<unsigned int, MAX_FLOOR> queue;
};
