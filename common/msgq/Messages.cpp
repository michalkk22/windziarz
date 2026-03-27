#include "Messages.hpp"

Messages::Messages(int flags) : mq_("/q", flags, {sizeof(Message), (mode_t)0644}) {}

void Messages::send(const Message &message) const
{
    mq_.send(reinterpret_cast<const char *>(&message), sizeof(message));
}

Message Messages::receive() const
{
    Message m;
    mq_.receive(reinterpret_cast<char *>(&m), sizeof(m));
    return m;
}

void Messages::unlink() const
{
    mq_.unlink();
}
