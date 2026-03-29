#include "Manager.hpp"

#include <memory>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "json.hpp"

#include "msgq/MessagesFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"
#include "utils/readJson.hpp"
#include "RequestsHandler.hpp"

Manager::Manager(UI *ui, std::atomic<bool> &running) : ui(ui),
                                                       messages(MessagesFactory::manager()),
                                                       shm(SharedMemoryFactory::create()),
                                                       running(running)
{
}

void Manager::loadConfig(const std::string &path)
{
    nlohmann::json j = readJson(path);

    cfg.floors = j["floors"];
    for (auto group : j["elevatorGroups"])
    {
        groups.push_back({group["min"],
                          group["max"],
                          group["count"]});
    }
    cfg.travelTime = j["travelTime"];
}

void Manager::start()
{
    try
    {
        // TODO:
        // create elevators
        // create persons
        runPersons();
        // start requests handler thread
        runRequestsHandler();

        // start ui
        ui->start(running, shm.get());

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

    // kill(personsPid, SIGINT); // not needed?
    waitpid(personsPid, nullptr, 0);
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
                                             { RequestsHandler{&messages, shm.get(), running}
                                                   .run(); });
}
