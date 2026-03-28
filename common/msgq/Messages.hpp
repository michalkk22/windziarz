#pragma once

#include <mqueue.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "Position.hpp"
#include "msgq/MessageQueue.hpp"

struct Message
{
    unsigned int floor;
    Direction direction;
    const char pipe[16];
};

class Messages
{
public:
    Messages(int flags, bool shouldUnlink = false);
    ~Messages();

    Messages(const Messages &) = delete;
    Messages &operator=(const Messages &) = delete;

    Messages(Messages &&) = default;
    Messages &operator=(Messages &&) = default;

    void send(const Message &message) const;
    Message receive() const;

private:
    MessageQueue mq_;
    bool shouldUnlink;
};
