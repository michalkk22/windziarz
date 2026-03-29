#include "FifoChannel.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>
// TODO: delete logs
#include <iostream>

FifoChannel::FifoChannel(const std::string &path, Mode mode, bool create)
    : path_(path), owner_(create)
{
    if (create)
    {
        if (mkfifo(path.c_str(), 0666) == -1 && errno != EEXIST)
        {
            throw std::runtime_error("mkfifo failed: " + std::string(strerror(errno)));
        }
    }

    int flags = (mode == Mode::Read) ? O_RDONLY : O_WRONLY;

    fd_ = open(path.c_str(), flags);
    if (fd_ == -1)
    {
        std::cout << path << std::endl;
        throw std::runtime_error("open failed: " + std::string(strerror(errno)));
    }
}

FifoChannel::~FifoChannel()
{
    if (fd_ != -1)
    {
        close(fd_);
    }
    if (owner_)
    {
        unlink(path_.c_str());
    }
}

FifoChannel::FifoChannel(FifoChannel &&other) noexcept
    : path_(std::move(other.path_)), fd_(other.fd_), owner_(other.owner_)
{
    other.fd_ = -1;
    other.owner_ = false;
}

FifoChannel &FifoChannel::operator=(FifoChannel &&other) noexcept
{
    if (this != &other)
    {
        fd_ = other.fd_;
        path_ = std::move(other.path_);
        owner_ = other.owner_;

        other.fd_ = -1;
        other.owner_ = false;
    }
    return *this;
}

void FifoChannel::sendInt(int value) const
{
    if (write(fd_, &value, sizeof(value)) != sizeof(value))
    {
        throw std::runtime_error("write failed");
    }
}

int FifoChannel::receiveInt() const
{
    int value;
    if (read(fd_, &value, sizeof(value)) != sizeof(value))
    {
        throw std::runtime_error("read failed");
    }
    return value;
}

std::string FifoChannel::getName() const
{
    size_t pos = path_.find_last_of("/");
    std::string name = path_.substr(pos + 1);
    return name;
}