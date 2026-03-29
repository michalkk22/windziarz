#include <memory>
#include <signal.h>
// TODO: delete logs
#include <iostream>

#include "Manager.hpp"
#include "EmptyUI.hpp"

std::atomic<bool> running(true);

void handleSignal(int)
{
    running = false;
    std::cerr << "Manager got signal" << std::endl;
}

int main()
{
    signal(SIGINT, handleSignal);
    auto ui = EmptyUI();
    Manager manager(&ui, running);
    manager.loadConfig("config.json");
    manager.start();
    return 0;
}
