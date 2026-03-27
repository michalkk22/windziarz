#pragma once

#include "UI.hpp"

class EmptyUI : public UI
{
public:
    EmptyUI() = default;

    void start(void *) override {};
    void stop() override {};
};