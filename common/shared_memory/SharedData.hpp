#pragma once

#include "../../elevator/ElevatorState.hpp"

struct SharedData
{
    int elevatorQueues;
    ElevatorState elevatorStates;
    Position personPositions;
};
