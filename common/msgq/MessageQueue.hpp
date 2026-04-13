#pragma once

#include <string>
#include <mqueue.h>

class MessageQueue
{
public:
    struct Config
    {
        long messageSize = 256;
        long maxMessages = 256;
        mode_t mode = 0644;
    };

    MessageQueue(const std::string &name, int flags, const Config &cfg);
    ~MessageQueue();

    // non-copyable
    MessageQueue(const MessageQueue &) = delete;
    MessageQueue &operator=(const MessageQueue &) = delete;

    // movable
    MessageQueue(MessageQueue &&other) noexcept;
    MessageQueue &operator=(MessageQueue &&other) noexcept;

    void send(const char *msg_ptr, size_t msg_len, unsigned int prio = 0) const;
    ssize_t receive(char *buffer, size_t buffer_len, unsigned int *prio = nullptr) const;

    void unlink() const;

private:
    mqd_t mq{-1};
    std::string name;
    struct mq_attr attr{};

    static std::string normalizeName(const std::string &name);
};