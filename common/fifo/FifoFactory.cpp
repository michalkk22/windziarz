#include "FifoFactory.hpp"

std::string FifoFactory::makePath(const std::string &name)
{
    return "/tmp/" + name;
}

FifoChannel FifoFactory::createReceiver(const std::string &name)
{
    return FifoChannel(makePath(name), FifoChannel::Mode::Read, true);
}

FifoChannel FifoFactory::createSender(const std::string &name)
{
    return FifoChannel(makePath(name), FifoChannel::Mode::Write);
}