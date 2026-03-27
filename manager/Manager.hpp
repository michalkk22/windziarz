#pragma once

#include "UI.hpp"
#include "../shared/Messages.hpp"

class Manager
{
public:
    Manager(UI *ui);

    void loadConfig(const std::string &path);
    void start();
    void stop();

private:
    Messages messages;
    UI *ui;

    struct Config
    {
        // elevators
        unsigned int floors;

        int travelTime;

        // persons
        int pauseTime;
        int maxPersons;
    } cfg;

    struct ElevatorGroup
    {
        unsigned int minFloor;
        unsigned int maxFloor;
        unsigned int count; // TODO: just count for now
    };
    std::vector<ElevatorGroup> groups;
};
