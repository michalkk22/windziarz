#include "Person.hpp"
#include <string>
#include <thread>
#include <vector>
#include <atomic>
#include <signal.h>
#include <mutex>
#include <condition_variable>
#include "utils/readJson.hpp"
#include "fifo/FifoFactory.hpp"

std::atomic<bool> running(true);
std::vector<FifoChannel> fifos;

int floors;
int interval;
int maxPersons;

int sigPipe[2];
void handleSignal(int)
{
    running = false;
    write(sigPipe[1], "a", 1);
}

void runPerson(int id);
void loadConfig(const std::string &path);

int main(int argc, char const *argv[])
{
    pipe(sigPipe);
    fcntl(sigPipe[0], F_SETFL, O_NONBLOCK);
    signal(SIGINT, handleSignal);
    loadConfig("config.json");

    // run Persons on threads
    std::vector<std::thread> persons;
    for (int i = 0; i < maxPersons && running; i++)
    {
        fifos.push_back(FifoFactory::createReceiver("person_" + std::to_string(i)));
        persons.emplace_back(runPerson, i);
        // wait interval
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }

    // wait for signal handler to write to pipe
    char buf;
    while (running)
    {
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
    // TODO: implement
    fifos[id].receiveInt();
}

void loadConfig(const std::string &path)
{
    nlohmann::json j = readJson(path);

    floors = j["floors"];
    maxPersons = j["maxPersons"];
    interval = j["personMinInterval"];
}
