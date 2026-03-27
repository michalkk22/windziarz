#pragma once

#include "UI.hpp"
#include <unistd.h>

class EmptyUI : public UI
{
public:
    EmptyUI() = default;

    void start(void *) override {
        sleep(10);
    };
    void stop() override {};
};