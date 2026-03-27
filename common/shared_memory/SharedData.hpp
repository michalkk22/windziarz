#pragma once

#include "ElevatorState.hpp"

struct SharedData
{
    int elevatorQueues;
    ElevatorState elevatorStates;
    Position personPositions;
};
