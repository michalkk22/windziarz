#pragma once

#include <atomic>

#include "msgq/Messages.hpp"
#include "shared_memory/SharedData.hpp"

class RequestsHandler
{
public:
    RequestsHandler(Messages *messages, SharedData *shm, std::atomic<bool> &running);

    void run();

private:
    Messages *messages;
    SharedData *shm;
    std::atomic<bool> &running;

    void handle(Message &msg);
};
