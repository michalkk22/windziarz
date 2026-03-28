#pragma once

#include "Position.hpp"
#include "msgq/Messages.hpp"
#include "fifo/FifoChannel.hpp"

class Person
{
public:
    Person(Position *position,
           unsigned int currentFloor,
           unsigned int destinationFloor,
           FifoChannel *fifo);

    void run();

private:
    Position *position;
    unsigned int destinationFloor;
    Messages messages;
    FifoChannel *fifo;
};