#include "Elevator.hpp"

#include "msgq/MessagesFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"

Elevator::Elevator(int id,
                   ElevatorState *state,
                   std::atomic<bool> &running)
    : id(id),
      state(state),
      running(running),
      messages(MessagesFactory::createElevatorRequests(std::to_string(id))),
      queueData(SharedMemoryFactory::joinElevatorQueue(std::to_string(id))),
      queue(queueData.get())
{
}

void Elevator::start()
{
    runRequestsHandler();
    run();
}

void Elevator::runRequestsHandler()
{
    requests = std::make_unique<std::thread>([this]()
                                             {
                                                 std::optional<FloorRequestMessage> msg;
                                                 while (running)
                                                 {
                                                     msg = messages.receive();
                                                     if (msg.has_value())
                                                     {
                                                         queue.addFloor(msg.value().floor);
                                                     }
                                                 }
                                                 queue.wakeUp(); // wake up main thread if was idle
                                             });
}

void Elevator::run()
{
    while (running)
    {
        unsigned int curr = state->floor;
        auto result = queue.updateAndGetNext(curr);

        if (result.shouldGoIdle)
        {
            updateState(curr);
            queue.goIdle();
            continue;
        }

        if (result.shouldOpenDoor)
        {
            openDoorForInterval();
            continue;
        }

        if (result.nextFloor > curr)
        {
            updateState(++curr, Direction::Up);
        }
        else if (result.nextFloor < curr)
        {
            updateState(--curr, Direction::Down);
        }

        if (!running) // don't wait, just shutdown
            break;

        wait(TRAVEL_TIME);
    }

    requests->join();
}

void Elevator::updateState(
    unsigned int floor,
    Direction direction,
    bool isDoorOpen)
{
    state->floor = floor;
    state->direction = direction;
    state->isDoorOpen = isDoorOpen;
}

void Elevator::openDoorForInterval()
{
    state->direction = Direction::None;
    state->isDoorOpen = true;
    wait(DOOR_INTERVAL);
}

void Elevator::wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}