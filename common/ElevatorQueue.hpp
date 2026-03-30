#pragma once

#include <optional>

#include "ElevatorQueueData.hpp"

class ElevatorQueue
{
public:
    ElevatorQueue(ElevatorQueueData *data);

    ElevatorQueueSnapshot getData();
    void addFloor(unsigned int floor);
    std::optional<unsigned int> updateAndGetNext(unsigned int floor);
    void goIdle();

private:
    ElevatorQueueData *data;

    void removeFloor();
    bool isAlreadyInQueue(unsigned int floor);
};

struct ElevatorQueueSnapshot
{
    unsigned int currentFloor;
    unsigned int queue[MAX_FLOOR];
    size_t size;
};