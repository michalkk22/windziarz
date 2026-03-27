#pragma once

struct Position
{
    unsigned int floor;
    Direction direction;
};

enum class Direction
{
    None,
    Up,
    Down
};