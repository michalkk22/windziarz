#pragma once

#include <mqueue.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "Direction.hpp"
#include "MessageQueue.hpp"

struct Message
{
    unsigned int floor;
    Direction direction;
    long pipe;
};

class Communication
{
public:
    Communication(int flags);
    void send(const Message &message) const;
    Message receive() const;
    void unlink() const;

private:
    MessageQueue mq_;
};
