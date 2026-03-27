#pragma once

class UI
{
public:
    virtual ~UI() = default;

    virtual void initialize() = 0;
    virtual void stop() = 0;
};
