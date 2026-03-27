#pragma once

#include "SharedMemory.hpp"

template <typename T>
class SharedMemoryFactory
{
public:
    SharedMemoryFactory() = delete;

    static SharedMemory<T> create();
    static SharedMemory<T> join();

    static std::string name = "shm";
};
