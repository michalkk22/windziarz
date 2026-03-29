#pragma once

#include "FifoChannel.hpp"
#include <memory>
#include <string>

class FifoFactory
{
public:
    // for Person: create FIFO and read from it
    static FifoChannel createReceiver(const std::string &name);

    // for Manager: connect and write
    static std::unique_ptr<FifoChannel> createSender(const std::string &name);

private:
    static std::string makePath(const std::string &name);
};