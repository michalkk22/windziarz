#include "Person.hpp"
#include "msgq/MessagesFactory.hpp"
#include <iostream>
#include <array>
#include <cstring>

Person::Person(Position *position,
               unsigned int currentFloor,
               unsigned int destinationFloor,
               FifoChannel *fifo,
               std::atomic<bool> &running)
    : position(position),
      destinationFloor(destinationFloor),
      messages(MessagesFactory::person()),
      fifo(fifo),
      running(running)
{
    // set your position
    *position = Position{currentFloor, Direction::None};
    std::cout << "My position is: floor " << position->floor << std::endl;
}

void Person::run()
{
    while (running && position->floor != destinationFloor)
    {
        std::cout << "Calling elevator to floor " << position->floor << std::endl;
        callElevator();
        std::cout << "Called elevator to floor " << position->floor << std::endl;

        // TODO:
        // receive elevator data
        int elevator = getElevatorData();
        std::cout << "Received elevator number " << elevator << std::endl;

        // wait for elevator

        // request floor

        // exit
    }
}

void Person::callElevator()
{
    if (!running)
        return;

    std::array<char, 16> pipe{};
    std::string name = fifo->getName();
    strncpy(pipe.data(), name.c_str(), name.size());
    pipe[pipe.size() - 1] = '\0'; // not sure if necessary or even correct

    Message msg = {
        (int)destinationFloor,
        destinationFloor > position->floor
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