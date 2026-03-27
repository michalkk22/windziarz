#pragma once

#include "Position.hpp"
#include "msgq/Messages.hpp"

class Person
{
public:
    Person(Position *position, unsigned int destinationFloor);

private:
    Position *position;
    unsigned int destinationFloor;
    Messages messages;
};