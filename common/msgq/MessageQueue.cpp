#include "MessageQueue.hpp"
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <ctime>

MessageQueue::MessageQueue(const std::string &name, int flags, const Config &cfg)
    : name(normalizeName(name))
{
    struct mq_attr attr{};
    attr.mq_msgsize = cfg.messageSize;
    attr.mq_maxmsg = cfg.maxMessages;

    mq = mq_open(name.c_str(), flags, cfg.mode, &attr);
    if (mq == (mqd_t)-1)
    {
        throw std::runtime_error("mq_open failed: " + std::string(strerror(errno)));
    }

    if (mq_getattr(mq, &attr) == -1)
    {
        throw std::runtime_error("mq_getattr failed: " + std::string(strerror(errno)));
    }
}

MessageQueue::~MessageQueue()
{
    if (mq != (mqd_t)-1)
    {
        mq_close(mq);
    }
}

MessageQueue::MessageQueue(MessageQueue &&other) noexcept
    : mq(other.mq), name(std::move(other.name)), attr(other.attr)
{
    other.mq = (mqd_t)-1;
}

MessageQueue &MessageQueue::operator=(MessageQueue &&other) noexcept
{
    if (this != &other)
    {
        mq = other.mq;
        name = std::move(other.name);
        attr = other.attr;
        other.mq = (mqd_t)-1;
    }
    return *this;
}

void MessageQueue::send(const char *msg_ptr, size_t msg_len, unsigned int prio) const
{
    if (msg_len > static_cast<size_t>(attr.mq_msgsize))
    {
        throw std::runtime_error("Message too large");
    }
    if (mq_send(mq, msg_ptr, msg_len, prio) == -1)
    {
        throw std::runtime_error("mq_send failed: " + std::string(strerror(errno)));
    }
}

ssize_t MessageQueue::receive(char *buffer, size_t buffer_len, unsigned int *prio) const
{
    if (buffer_len < static_cast<size_t>(attr.mq_msgsize))
    {
        throw std::runtime_error("Buffer too small");
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 1;

    ssize_t bytes = mq_timedreceive(mq, buffer, buffer_len, prio, &ts);

    if (bytes == -1 && errno != ETIMEDOUT)
    {
        throw std::runtime_error("mq_receive failed: " + std::string(strerror(errno)));
    }

    return bytes;
}

void MessageQueue::unlink() const
{
    if (mq_unlink(name.c_str()) == -1)
    {
        throw std::runtime_error("mq_unlink failed: " + std::string(strerror(errno)));
    }
}

std::string MessageQueue::normalizeName(const std::string &name)
{
    if (name.empty())
    {
        return "/q";
    }
    if (name[0] != '/')
    {
        return "/" + name;
    }
    return name;
}