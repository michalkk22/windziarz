#pragma once

#include "Direction.hpp"

struct ElevatorState
{
    unsigned int floor;
    bool isDoorOpen;
    Direction direction;
};
