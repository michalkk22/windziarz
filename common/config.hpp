#pragma once

struct ElevatorGroupConfig
{
    unsigned int count;
    unsigned int minFloor;
    unsigned int maxFloor;
};

constexpr int MAX_FLOOR = 10;

constexpr int PERSON_COUNT = 2;
constexpr int PERSON_INTERVAL = 5;

constexpr int ELEVATOR_COUNT = 8;
constexpr ElevatorGroupConfig ELEVATOR_GROUPS[3]{
    {2, 0, 5},
    {2, 5, 10},
    {2, 0, 10},
};

constexpr int TRAVEL_TIME = 4;
constexpr int DOOR_INTERVAL = 2;
