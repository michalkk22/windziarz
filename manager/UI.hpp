#pragma once

class UI
{
public:
    virtual ~UI() = default;

    virtual void start(void *) = 0;
    virtual void stop() = 0;
};
