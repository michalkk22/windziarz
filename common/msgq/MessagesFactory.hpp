#pragma once

#include "Messages.hpp"
#include "CallElevatorMessage.hpp"

class MessagesFactory
{
public:
    static Messages<CallElevatorMessage> manager();
    static Messages<CallElevatorMessage> person();
};