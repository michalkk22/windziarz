#pragma once

#include <atomic>
#include <optional>

#include "ElevatorQueueData.hpp"

struct ElevatorQueueSnapshot
{
    unsigned int currentFloor;
    unsigned int queue[MAX_FLOOR];
    size_t size;
};

struct UpdateResult
{
    bool shouldGoIdle = false;
    bool shouldOpenDoor = false;
    unsigned int nextFloor = 0;
};

class ElevatorQueue
{
public:
    ElevatorQueue(ElevatorQueueData *data);

    ElevatorQueueSnapshot getData();
    void addFloor(unsigned int floor);
    UpdateResult updateAndGetNext(unsigned int floor);
    void goIdle();
    void wakeUp();

private:
    ElevatorQueueData *data;

    void removeFloor();
    bool isAlreadyInQueue(unsigned int floor);
};