#pragma once

#include <atomic>

#include "msgq/Messages.hpp"
#include "msgq/CallElevatorMessage.hpp"
#include "fifo/FifoChannel.hpp"
#include "PersonState.hpp"

class Person
{
public:
    Person(PersonState *state,
           unsigned int currentFloor,
           unsigned int destinationFloor,
           FifoChannel *fifo,
           std::atomic<bool> &running);

    void run();

private:
    PersonState *state;
    unsigned int destinationFloor;
    Messages<CallElevatorMessage> messages;
    FifoChannel *fifo;
    std::atomic<bool> &running;

    void updateState(const int elevator, const unsigned int floor = -1);
    void callElevator();
    int getElevatorData();
    void waitForElevatorAndEnter();
};