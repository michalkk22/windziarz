#include "Person.hpp"
#include "msgq/MessagesFactory.hpp"
#include <iostream>

Person::Person(Position *position,
               unsigned int currentFloor,
               unsigned int destinationFloor,
               FifoChannel *fifo)
    : position(position),
      destinationFloor(destinationFloor),
      messages(MessagesFactory::person()),
      fifo(fifo)
{
    *position = Position{currentFloor, Direction::None};
}

void Person::run()
{
    while (position->floor != destinationFloor)
    {
        // call elevator by sending request to manager
        Message msg = {
            destinationFloor,
            destinationFloor > position->floor
                ? Direction::Up
                : Direction::Down,
            *fifo->getPath().c_str(),
        };
        messages.send(msg);

        // TODO:
        // receive elevator data
        int asd = fifo->receiveInt();
        std::cout << "GOT INT " << asd << std::endl;

        // wait for elevator

        // request floor

        // exit
    }
};