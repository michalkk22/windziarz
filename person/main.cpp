#include "Person.hpp"
#include <string>
#include <thread>
#include <vector>
#include <atomic>
#include <signal.h>
#include <mutex>
#include <random>
#include <condition_variable>
// TODO: delete logs
#include <iostream>

#include "config.hpp"
#include "fifo/FifoFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"
#include "shared_memory/States.hpp"

std::atomic<bool> running(true);

std::vector<FifoChannel> fifos;
States *shm;

int sigPipe[2];
void handleSignal(int)
{
    std::cerr << "Person got signal" << std::endl;
    running = false;
    write(sigPipe[1], "a", 1);
}

std::random_device rd;
std::mt19937 gen(rd());

void runPerson(int id);
void waitInterval();

int main()
{
    pipe(sigPipe);
    fcntl(sigPipe[0], F_SETFL, O_NONBLOCK);
    signal(SIGINT, handleSignal);

    auto shmObj = SharedMemoryFactory::join();
    shm = shmObj.get();

    // run Persons on threads
    std::vector<std::thread> persons;
    fifos.reserve(PERSON_COUNT);
    for (int i = 0; i < PERSON_COUNT && running; i++)
    {
        std::cout << "Creating threads: fifo " << i << std::endl;
        fifos.push_back(FifoFactory::createReceiver("person_" + std::to_string(i)));
        std::cout << "Creating threads: Person_" << i << std::endl;
        persons.emplace_back(runPerson, i);
        waitInterval();
    }

    // wait for signal handler to write to pipe
    char buf;
    while (running)
    {
        std::cout << "Persons ready, waiting for signal..." << std::endl;
        int n = read(sigPipe[0], &buf, 1);
        if (n > 0)
            break;
    }

    // detatch threads
    for (auto &t : persons)
    {
        t.detach();
    }

    return 0;
}

void runPerson(int id)
{
    std::cout << "Starting Person_" << id << std::endl;
    std::uniform_int_distribution<> dist(0, MAX_FLOOR);
    unsigned int curr = 0, dest = 0;
    // TODO: shared memory data: use correct pointer
    PersonState *state = &shm->personStates[id];

    while (running)
    {
        curr = dist(gen);
        do
            dest = dist(gen);
        while (curr == dest);

        std::cout << "Running Person_" << id << " with " << curr << " " << dest << std::endl;

        Person(
            state,
            curr,
            dest,
            &fifos[id],
            running)
            .run();

        waitInterval();
    }
}

void waitInterval()
{
    std::this_thread::sleep_for(std::chrono::seconds(PERSON_INTERVAL));
}
