#pragma once

#include <array>

#include "config.hpp"
#include "ElevatorState.hpp"
#include "PersonState.hpp"

struct States
{
    std::array<ElevatorState, ELEVATOR_COUNT> elevatorStates;
    std::array<PersonState, PERSON_COUNT> personStates;
};
