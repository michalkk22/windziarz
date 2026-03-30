#pragma once

#include "SharedMemory.hpp"
#include "States.hpp"
#include "ElevatorQueueData.hpp"

class SharedMemoryFactory
{
public:
    SharedMemoryFactory() = delete;

    static SharedMemory<States> createStates();
    static SharedMemory<States> joinStates();

    static SharedMemory<ElevatorQueueData> createElevatorQueue(std::string id);
    static SharedMemory<ElevatorQueueData> joinElevatorQueue(std::string id);
};