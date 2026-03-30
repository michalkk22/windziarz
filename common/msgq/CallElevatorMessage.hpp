#pragma once

#include <array>

#include "Direction.hpp"

struct CallElevatorMessage
{
    int floor;
    Direction direction;
    std::array<char, 16> pipe;
};