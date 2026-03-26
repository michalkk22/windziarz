#include "Communication.hpp"

Communication::Communication(int flags) : mq_("/q", flags, {sizeof(Message), (mode_t)0644}) {}

void Communication::send(const Message &message) const
{
    mq_.send(reinterpret_cast<const char *>(&message), sizeof(message));
}

Message Communication::receive() const
{
    Message m;
    mq_.receive(reinterpret_cast<char *>(&m), sizeof(m));
}

void Communication::unlink() const
{
}
