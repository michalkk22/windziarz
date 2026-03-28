#pragma once

#include "SharedMemory.hpp"
#include "SharedData.hpp"

class SharedMemoryFactory
{
public:
    SharedMemoryFactory() = delete;

    static SharedMemory<SharedData> create()
    {
        return SharedMemory<SharedData>("shmem", true);
    }

    static SharedMemory<SharedData> join()
    {
        return SharedMemory<SharedData>("shmem");
    }
};