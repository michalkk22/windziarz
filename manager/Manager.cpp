#include "Manager.hpp"

#include <memory>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "config.hpp"
#include "msgq/MessagesFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"
#include "utils/readJson.hpp"
#include "RequestsHandler.hpp"

Manager::Manager(UI *ui, std::atomic<bool> &running) : ui(ui),
                                                       messages(MessagesFactory::manager()),
                                                       states(SharedMemoryFactory::createStates()),
                                                       running(running)
{
    loadConfig();
}

void Manager::start()
{
    try
    {
        // TODO:
        // create elevators
        runElevators();
        // create persons
        runPersons();
        // start requests handler thread
        runRequestsHandler();

        // start ui
        ui->start(running, states.get());

        // gets here when UI stop -> running == false
        stop();
    }
    catch (const std::exception &e)
    {
        running = false;
        stop();
    }
}

void Manager::stop()
{
    // TODO:
    // clean all

    requests->join();

    // kill(personsPid, SIGINT); // not needed? yup, it's not
    waitpid(personsPid, nullptr, 0);

    for (auto p : elevatorPids)
        waitpid(p, nullptr, 0);
}

void Manager::loadConfig()
{
    for (auto group : ELEVATOR_GROUPS)
        for (int i = 0; i < group.count; i++)
            elevators.push_back({group.minFloor,
                                 group.maxFloor});
}

void Manager::runElevators()
{
    int id = 0;
    for (auto e : elevators)
    {
        auto qshm = SharedMemoryFactory::createElevatorQueue(std::to_string(id));
        // TODO: implement
        id++;
    }
}

void Manager::runPersons()
{
    personsPid = fork();
    if (personsPid == -1)
    {
        throw std::runtime_error("fork failed: " + std::string(strerror(errno)));
    }

    if (personsPid == 0)
    {
        execl("./person", "person", nullptr);
        throw std::runtime_error("execl failed: " + std::string(strerror(errno)));
    }
}

void Manager::runRequestsHandler()
{
    requests = std::make_unique<std::thread>([this]()
                                             { RequestsHandler(&messages, states.get(), running)
                                                   .run(); });
}
