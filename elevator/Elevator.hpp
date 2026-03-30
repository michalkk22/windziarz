#pragma once

#include <thread>

#include "msgq/Messages.hpp"
#include "msgq/FloorRequestMessage.hpp"
#include "shared_memory/SharedMemory.hpp"
#include "ElevatorQueueData.hpp"
#include "ElevatorState.hpp"
#include "ElevatorQueue.hpp"

class Elevator
{
public:
    Elevator(int id,
             ElevatorState *state,
             std::atomic<bool> &running);

    void start();

private:
    int id;
    ElevatorState *state;
    std::atomic<bool> &running;
    Messages<FloorRequestMessage> messages;
    SharedMemory<ElevatorQueueData> queueData;
    ElevatorQueue queue;

    std::unique_ptr<std::thread> requests;
    void runRequestsHandler();

    void run();
    void updateState(
        unsigned int floor,
        Direction direction = Direction::None,
        bool isDoorOpen = false);
    void openDoorForInterval();
    void wait(int seconds);
};