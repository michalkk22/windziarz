#pragma once

#include "../common/Position.hpp"

struct ElevatorState
{
    bool isDoorOpen;
    Position *position;
};
