#pragma once

#include <atomic>
#include <thread>
#include <vector>

#include "UI.hpp"
#include "msgq/Messages.hpp"
#include "shared_memory/SharedMemory.hpp"
#include "shared_memory/SharedData.hpp"

class Manager
{
public:
    Manager(UI *ui, std::atomic<bool> &running);

    void loadConfig(const std::string &path);
    void start();
    void stop();

private:
    UI *ui;
    Messages messages;
    SharedMemory<SharedData> shm;

    struct Config
    {
        // elevators
        unsigned int floors;

        int travelTime;
    } cfg;

    struct ElevatorGroup
    {
        unsigned int minFloor;
        unsigned int maxFloor;
        unsigned int count; // TODO: just count for now
    };
    std::vector<ElevatorGroup> groups;

    pid_t personsPid;
    void runPersons();

    std::atomic<bool> &running;
    std::unique_ptr<std::thread> requests;
    void runRequestsHandler();
};
