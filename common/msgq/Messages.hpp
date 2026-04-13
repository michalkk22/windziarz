#pragma once

#include <mqueue.h>
#include <stdexcept>
#include <array>
#include <optional>

#include "Direction.hpp"
#include "msgq/MessageQueue.hpp"

template <typename T>
class Messages
{
public:
    Messages(const std::string &name,
             long msgSize,
             int flags,
             bool shouldUnlink = false)
        : mq(name,
             flags,
             MessageQueue::Config{msgSize, 10, (mode_t)0644}),
          shouldUnlink(shouldUnlink) {}

    ~Messages()
    {
        if (shouldUnlink)
            mq.unlink();
    }

    Messages(const Messages &) = delete;
    Messages &operator=(const Messages &) = delete;

    Messages(Messages &&) = default;
    Messages &operator=(Messages &&) = default;

    void send(const T &message) const
    {
        mq.send(reinterpret_cast<const char *>(&message), sizeof(message));
    }

    std::optional<T> receive() const
    {
        T msg;
        ssize_t result = mq.receive(reinterpret_cast<char *>(&msg), sizeof(msg));
        if (result == -1)
        {
            return std::nullopt;
        }
        return msg;
    }

private:
    MessageQueue mq;
    bool shouldUnlink;
};
