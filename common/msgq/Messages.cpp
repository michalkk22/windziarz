#include "Messages.hpp"

Messages::Messages(int flags, bool shouldUnlink) : mq_("/q", flags, MessageQueue::Config{sizeof(Message), 10, (mode_t)0644}), shouldUnlink(shouldUnlink) {}

Messages::~Messages()
{
    if (shouldUnlink)
    {
        mq_.unlink();
    }
}

void Messages::send(const Message &message) const
{
    mq_.send(reinterpret_cast<const char *>(&message), sizeof(message));
}

Message Messages::receive() const
{
    Message m;
    ssize_t result = mq_.receive(reinterpret_cast<char *>(&m), sizeof(m));
    if (result == -1)
    {
        m.floor = -1;
    }
    return m;
}