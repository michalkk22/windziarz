#include "FifoChannel.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdexcept>
#include <cstring>
// TODO: delete logs
#include <iostream>

FifoChannel::FifoChannel(const std::string &path, Mode mode, bool create)
    : path(path), owner(create)
{
    if (create)
    {
        if (mkfifo(path.c_str(), 0666) == -1 && errno != EEXIST)
        {
            throw std::runtime_error("mkfifo failed: " + std::string(strerror(errno)));
        }
    }

    int flags = (mode == Mode::Read) ? O_RDWR : O_WRONLY;

    fd = open(path.c_str(), flags);
    if (fd == -1)
    {
        std::cout << path << std::endl;
        throw std::runtime_error("open failed: " + std::string(strerror(errno)));
    }
}

FifoChannel::~FifoChannel()
{
    if (fd != -1)
    {
        close(fd);
    }
    if (owner)
    {
        unlink(path.c_str());
    }
}

FifoChannel::FifoChannel(FifoChannel &&other) noexcept
    : path(std::move(other.path)), fd(other.fd), owner(other.owner)
{
    other.fd = -1;
    other.owner = false;
}

FifoChannel &FifoChannel::operator=(FifoChannel &&other) noexcept
{
    if (this != &other)
    {
        fd = other.fd;
        path = std::move(other.path);
        owner = other.owner;

        other.fd = -1;
        other.owner = false;
    }
    return *this;
}

void FifoChannel::sendInt(int value) const
{
    if (write(fd, &value, sizeof(value)) != sizeof(value))
    {
        throw std::runtime_error("write failed");
    }
}

int FifoChannel::receiveInt() const
{
    int value;

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;

    int result = poll(&pfd, 1, 1000);
    if (result > 0)
    {
        if (pfd.revents & POLLIN)
        {
            if (read(fd, &value, sizeof(value)) != sizeof(value))
            {
                throw std::runtime_error("read failed");
            }
        }
    }
    else if (result == 0)
    {
        // timeout
        return -1;
    }
    else
    {
        throw std::runtime_error("poll failed");
    }

    return value;
}

std::string FifoChannel::getName() const
{
    size_t pos = path.find_last_of("/");
    std::string name = path.substr(pos + 1);
    return name;
}