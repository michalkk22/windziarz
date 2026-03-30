#pragma once

#include "shmNames.hpp"
#include "SharedMemory.hpp"
#include "States.hpp"
#include "ElevatorQueueData.hpp"

class SharedMemoryFactory
{
public:
    SharedMemoryFactory() = delete;

    static SharedMemory<States> createStates()
    {
        return SharedMemory<States>(SHM_STATES, true);
    }

    static SharedMemory<States> joinStates()
    {
        return SharedMemory<States>(SHM_STATES);
    }

    static SharedMemory<ElevatorQueueData> createElevatorQueue(std::string id)
    {
        SharedMemory<ElevatorQueueData> shm(SHM_ELEVATOR_QUEUE_PREFIX, true);

        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

        pthread_mutex_init(&shm.get()->mutex, &attr);

        return shm;
    }

    static SharedMemory<ElevatorQueueData> joinElevatorQueue(std::string id)
    {
        return SharedMemory<ElevatorQueueData>(SHM_ELEVATOR_QUEUE_PREFIX + id);
    }
};