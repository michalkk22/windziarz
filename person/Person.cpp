#include "Person.hpp"
#include "msgq/MessagesFactory.hpp"

Person::Person(Position *position, unsigned int destinationFloor) : position(position), destinationFloor(destinationFloor), messages(MessagesFactory::person())
{
}
void Person::run()
{
    unsigned int currentFloor, destinationFloor;
    while (currentFloor != destinationFloor)
    {
        // call elevator by sending request to manager

        // receive elevator data

        // wait for elevator

        // request floor

        // exit
    }
};