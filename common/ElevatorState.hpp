#pragma once

#include <atomic>

#include "Direction.hpp"

struct ElevatorState
{
    unsigned int floor;
    std::atomic<bool> isDoorOpen;
    Direction direction;
};
