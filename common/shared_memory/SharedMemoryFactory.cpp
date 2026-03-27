#include "SharedMemoryFactory.hpp"

template <typename T>
SharedMemory<T> SharedMemoryFactory<T>::create()
{
    return SharedMemory<T>(name, true);
}

template <typename T>
SharedMemory<T> SharedMemoryFactory<T>::join()
{
    return SharedMemory<T>(name);
}
