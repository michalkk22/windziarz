#pragma once

#include "UI.hpp"

class EmptyUI : public UI
{
public:
    EmptyUI() = default;

    void initialize() override {};
    void stop() override {};
};