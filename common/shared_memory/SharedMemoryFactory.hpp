#pragma once

#include "SharedMemory.hpp"
#include "States.hpp"

class SharedMemoryFactory
{
public:
    SharedMemoryFactory() = delete;

    static SharedMemory<States> create()
    {
        return SharedMemory<States>("shmem", true);
    }

    static SharedMemory<States> join()
    {
        return SharedMemory<States>("shmem");
    }
};