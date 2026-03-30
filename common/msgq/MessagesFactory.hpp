#pragma once

#include "Messages.hpp"
#include "CallElevatorMessage.hpp"
#include "FloorRequestMessage.hpp"

class MessagesFactory
{
public:
    static Messages<CallElevatorMessage> manager();
    static Messages<CallElevatorMessage> person();

    static Messages<FloorRequestMessage> createElevatorRequests(std::string id);
    static Messages<FloorRequestMessage> joinElevatorRequests(std::string id);
};