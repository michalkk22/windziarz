#include "Person.hpp"
#include "msgq/MessagesFactory.hpp"

Person::Person(Position *position, unsigned int destinationFloor) : position(position), destinationFloor(destinationFloor), messages(MessagesFactory::person()) {
                                                                    };