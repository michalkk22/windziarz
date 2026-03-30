#include "Person.hpp"
#include "msgq/MessagesFactory.hpp"
#include <iostream>
#include <array>
#include <cstring>

Person::Person(PersonState *state,
               unsigned int currentFloor,
               unsigned int destinationFloor,
               FifoChannel *fifo,
               std::atomic<bool> &running)
    : state(state),
      destinationFloor(destinationFloor),
      messages(MessagesFactory::person()),
      fifo(fifo),
      running(running)
{
    // set your state
    updateState(-1, currentFloor);
    std::cout << "My state is: floor " << state->floor << std::endl;
}

void Person::run()
{
    while (running && state->floor != destinationFloor)
    {
        std::cout << "Calling elevator to floor " << state->floor << std::endl;
        callElevator();
        std::cout << "Called elevator to floor " << state->floor << std::endl;

        // TODO:
        // receive elevator data
        int elevator = getElevatorData();
        std::cout << "Received elevator number " << elevator << std::endl;
        break;

        // wait for elevator

        updateState(elevator);
        // request floor

        // exit
    }
    std::cout << "Person finished running" << std::endl;
}

void Person::updateState(const int elevator, const unsigned int floor)
{
    // TODO: synchro mutex
    state->inElevator = elevator;
    state->floor = floor;
}

void Person::callElevator()
{
    if (!running)
        return;

    std::array<char, 16> pipe{};
    std::string name = fifo->getName();
    strncpy(pipe.data(), name.c_str(), name.size());
    pipe[pipe.size() - 1] = '\0'; // not sure if necessary or even correct

    CallElevatorMessage msg = {
        (int)destinationFloor,
        destinationFloor > state->floor
            ? Direction::Up
            : Direction::Down,
        pipe,
    };
    messages.send(msg);
}

int Person::getElevatorData()
{
    int elevator = -1;
    while (running)
    {
        elevator = fifo->receiveInt();
        if (elevator != -1)
            break;
    }
    return elevator;
};