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

    for (size_t i = d.size; i > 0; --i)
    {
        d.queue[i] = d.queue[i - 1];
    }
    d.queue[0] = floor;
    ++d.size;

    if (isIdle)
    {
        pthread_cond_signal(&d.idleCond);
    }
    pthread_mutex_unlock(&d.mutex);
}

std::optional<unsigned int> ElevatorQueue::updateAndGetNext(unsigned int floor)
{
    auto &d = *data;
    pthread_mutex_lock(&d.mutex);

    d.currentFloor = floor;
    if (d.size > 0 && floor == d.queue[0])
        removeFloor();

    std::optional<unsigned int> next;
    next = -1;
    if (d.size > 0)
    {
        next = d.queue[0];
    }
    pthread_mutex_unlock(&d.mutex);
    return next;
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