#pragma once

#include <atomic>
#include <thread>
#include <vector>

#include "UI.hpp"
#include "msgq/Messages.hpp"
#include "msgq/CallElevatorMessage.hpp"
#include "shared_memory/SharedMemory.hpp"
#include "shared_memory/States.hpp"

class Manager
{
public:
    Manager(UI *ui, std::atomic<bool> &running);

    void start();
    void stop();

private:
    UI *ui;
    Messages<CallElevatorMessage> messages;
    SharedMemory<States> states;
    std::atomic<bool> &running;

    struct ElevatorGroup
    {
        unsigned int count; // TODO: just count for now
        unsigned int minFloor;
        unsigned int maxFloor;
    };
    std::vector<ElevatorGroup> groups;

    void loadConfig();

    // Persons
    pid_t personsPid;
    void runPersons();

    // RequestsHandler
    std::unique_ptr<std::thread> requests;
    void runRequestsHandler();
};
