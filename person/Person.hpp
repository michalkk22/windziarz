#pragma once

#include <atomic>

#include "Position.hpp"
#include "msgq/Messages.hpp"
#include "fifo/FifoChannel.hpp"

class Person
{
public:
    Person(Position *position,
           unsigned int currentFloor,
           unsigned int destinationFloor,
           FifoChannel *fifo,
           std::atomic<bool> &running);

    void run();

private:
    Position *position;
    unsigned int destinationFloor;
    Messages messages;
    FifoChannel *fifo;
    std::atomic<bool> &running;

    void callElevator();
    int getElevatorData();
    void waitForElevatorAndEnter();
};