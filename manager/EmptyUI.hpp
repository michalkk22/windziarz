#pragma once

#include "UI.hpp"
#include <unistd.h>

class EmptyUI : public UI
{
public:
    EmptyUI() = default;

    void start(std::atomic<bool> &running, void *) override
    {
        while (running)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };
};