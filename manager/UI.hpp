#pragma once

#include <atomic>

class UI
{
public:
    virtual ~UI() = default;

    virtual void start(std::atomic<bool> &running, void *) = 0;
};
