#include "Manager.hpp"

#include <memory>
#include <fstream>
#include <libs/json.hpp>

#include "../common/msgq/MessagesFactory.hpp"
#include "../common/shared_memory/SharedMemory.hpp"
#include "../common/shared_memory/SharedData.hpp"
#include "EmptyUI.hpp"

using json = nlohmann::json;

Manager::Manager(UI *ui) : ui(ui), messages(MessagesFactory::manager())
{
}

void Manager::loadConfig(const std::string &path)
{
    std::ifstream file(path);

    if (!file)
    {
        throw std::runtime_error("Cannot open config file");
    }

    json j;
    file >> j;

    cfg.floors = j["floors"];
    for (auto group : j["elevatorGroups"])
    {
        groups.push_back({group["min"],
                          group["max"],
                          group["count"]});
    }
    cfg.travelTime = j["travelTime"];
    cfg.maxPersons = j["maxPersons"];
    cfg.pauseTime = j["pauseTime"];
}

void Manager::start()
{
    // TODO:
    // create shared memory
    SharedMemory<SharedData> shm("shmem", true);
    // start ui thread
    // create elevators
    // create mq for persons requests
    // start persons interface
    // start handling requests
}

void Manager::stop()
{
    // TODO:
    // clean all
}
