#include "Manager.hpp"

#include <memory>
#include <fstream>
#include "json.hpp"

#include "msgq/MessagesFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"

using json = nlohmann::json;

Manager::Manager(UI *ui) : ui(ui), messages(MessagesFactory::manager()), shm(SharedMemoryFactory::create())
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
    // create elevators
    // start requests handler thread

    // start ui
    ui->start(shm.get());
}

void Manager::stop()
{
    // TODO:
    // clean all
}
