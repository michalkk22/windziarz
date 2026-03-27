#pragma once

enum class Direction
{
    None,
    Up,
    Down
};

struct Position
{
    unsigned int floor;
    Direction direction;
};
