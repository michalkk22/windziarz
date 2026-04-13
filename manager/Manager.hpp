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

private:
    UI *ui;
    Messages<CallElevatorMessage> messages;
    SharedMemory<States> states;
    std::atomic<bool> &running;

    void stop();

    struct ElevatorRange
    {
        unsigned int minFloor;
        unsigned int maxFloor;
    };
    std::vector<ElevatorRange> elevators;

    void loadConfig();

    // Elevators
    std::vector<pid_t> elevatorPids;
    void runElevators();

    // Persons
    pid_t personsPid;
    void runPersons();

    // RequestsHandler
    std::unique_ptr<std::thread> requests;
    void runRequestsHandler();
};
