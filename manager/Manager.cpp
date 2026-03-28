#include "Manager.hpp"

#include <memory>
#include <fstream>
#include "json.hpp"

#include "msgq/MessagesFactory.hpp"
#include "shared_memory/SharedMemoryFactory.hpp"
#include "utils/readJson.hpp"

Manager::Manager(UI *ui) : ui(ui), messages(MessagesFactory::manager()), shm(SharedMemoryFactory::create())
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
    // TODO:
    // create persons
    runPersons();
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

void Manager::runPersons()
{
    personsPid = fork();
    if (personsPid == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if (personsPid)
    {
        execl("./person", "person", nullptr);
    }
}
