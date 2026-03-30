#pragma once

#include "ElevatorState.hpp"
#include "PersonState.hpp"
#include "config.hpp"

struct States
{
    ElevatorState elevatorStates[ELEVATOR_COUNT];
    PersonState personStates[PERSON_COUNT];
};
