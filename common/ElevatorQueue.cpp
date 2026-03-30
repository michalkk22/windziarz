#include "ElevatorQueue.hpp"

#include <string>

ElevatorQueue::ElevatorQueue(ElevatorQueueData *data) : data(data)
{
}

ElevatorQueueSnapshot ElevatorQueue::getData()
{
    auto &d = *data;
    pthread_mutex_lock(&d.mutex);

    ElevatorQueueSnapshot snap;
    snap.currentFloor = d.currentFloor;
    snap.size = d.size;
    std::copy(d.queue, d.queue + d.size, snap.queue);

    pthread_mutex_unlock(&d.mutex);
    return snap;
}

void ElevatorQueue::addFloor(unsigned int floor)
{
    auto &d = *data;
    pthread_mutex_lock(&d.mutex);

    if (d.size >= MAX_FLOOR || isAlreadyInQueue(floor))
    {
        pthread_mutex_unlock(&d.mutex);
        return;
    }

    bool isIdle = d.size == 0;

    // I can only go so far...
    if (floor > d.maxFloor)
        floor = d.maxFloor;
    if (floor < d.minFloor)
        floor = d.minFloor;

    for (size_t i = d.size; i > 0; --i)
    {
        d.queue[i] = d.queue[i - 1];
    }
    d.queue[0] = floor;
    ++d.size;

    if (isIdle)
        wakeUp();

    pthread_mutex_unlock(&d.mutex);
}

UpdateResult ElevatorQueue::updateAndGetNext(unsigned int currentFloor)
{
    auto &d = *data;
    pthread_mutex_lock(&d.mutex);

    UpdateResult result;

    d.currentFloor = currentFloor;
    if (d.size > 0)
    {
        if (currentFloor == d.queue[0])
        {
            result.shouldOpenDoor = true;
            removeFloor();
            pthread_mutex_unlock(&d.mutex);
            return result;
        }

        result.nextFloor = d.queue[0];
    }
    else
    {
        result.shouldGoIdle = true;
    }

    pthread_mutex_unlock(&d.mutex);
    return result;
}

void ElevatorQueue::goIdle()
{
    auto &d = *data;
    pthread_mutex_lock(&d.mutex);

    while (d.size == 0)
    {
        pthread_cond_wait(&d.idleCond, &d.mutex);
    }

    pthread_mutex_unlock(&d.mutex);
}

void ElevatorQueue::wakeUp()
{
    pthread_cond_signal(&data->idleCond);
}

void ElevatorQueue::removeFloor()
{
    auto &d = *data;

    for (size_t i = 1; i < d.size; ++i)
    {
        d.queue[i - 1] = d.queue[i];
    }
    --d.size;
}

bool ElevatorQueue::isAlreadyInQueue(unsigned int floor)
{
    auto &d = *data;
    bool isAlreadyInQueue = false;
    for (size_t i = 0; i < d.size; ++i)
    {
        if (d.queue[i] == floor)
        {
            isAlreadyInQueue = true;
            break;
        }
    }
    return isAlreadyInQueue;
}