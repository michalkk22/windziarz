#pragma once

#include <atomic>

#include "msgq/Messages.hpp"
#include "msgq/CallElevatorMessage.hpp"
#include "shared_memory/States.hpp"

class RequestsHandler
{
public:
    RequestsHandler(Messages<CallElevatorMessage> *messages, States *shm, std::atomic<bool> &running);

    void run();

private:
    Messages<CallElevatorMessage> *messages;
    States *shm;
    std::atomic<bool> &running;

    void handle(CallElevatorMessage &msg);
};
