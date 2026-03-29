#pragma once

#include <mqueue.h>
#include <stdexcept>
#include <array>

#include "Position.hpp"
#include "msgq/MessageQueue.hpp"

struct Message
{
    int floor;
    Direction direction;
    std::array<char, 16> pipe;
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
