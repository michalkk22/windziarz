#pragma once

#include "../shared/Position.hpp"
#include "../shared/Messages.hpp"

class Person
{
public:
    Person(Position *position, unsigned int destinationFloor);

private:
    Position *position;
    unsigned int destinationFloor;
    Messages messages;
};