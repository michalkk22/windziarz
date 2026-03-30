#include "SharedMemoryFactory.hpp"

#include "shmNames.hpp"

SharedMemory<States> SharedMemoryFactory::createStates()
{
    return SharedMemory<States>(SHM_STATES, true);
}

SharedMemory<States> SharedMemoryFactory::joinStates()
{
    return SharedMemory<States>(SHM_STATES);
}

SharedMemory<ElevatorQueueData> SharedMemoryFactory::createElevatorQueue(std::string id)
{
    SharedMemory<ElevatorQueueData> shm(SHM_ELEVATOR_QUEUE_PREFIX + id, true);

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&shm.get()->mutex, &attr);

    return shm;
}

SharedMemory<ElevatorQueueData> SharedMemoryFactory::joinElevatorQueue(std::string id)
{
    return SharedMemory<ElevatorQueueData>(SHM_ELEVATOR_QUEUE_PREFIX + id);
}