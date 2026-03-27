#include <memory>

#include "Manager.hpp"
#include "EmptyUI.hpp"

int main(int argc, char const *argv[])
{
    auto ui = EmptyUI();
    Manager manager{&ui};
    manager.loadConfig("config.json");
    manager.start();
    return 0;
}
