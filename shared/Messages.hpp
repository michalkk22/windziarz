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

class Messages
{
public:
    Messages(int flags);

    Messages(const Messages &) = delete;
    Messages &operator=(const Messages &) = delete;

    Messages(Messages &&) = default;
    Messages &operator=(Messages &&) = default;

    void send(const Message &message) const;
    Message receive() const;
    void unlink() const;

private:
    MessageQueue mq_;
};
