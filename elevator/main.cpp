#include <atomic>
#include <stdexcept>
#include <signal.h>
// TODO: delete logs
#include <iostream>

#include "Elevator.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"

std::atomic<bool> running(true);

void handleSignal(int)
{
    running = false;
    std::cerr << "Elevator got signal" << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid agruments count");
    }
    int id = atoi(argv[1]);

    signal(SIGINT, handleSignal);

    auto shmStates = SharedMemoryFactory::joinStates();
    ElevatorState *state = &shmStates.get()->elevatorStates.at(id);

    Elevator elevator(id, state, running);
    elevator.start();

    return 0;
}
