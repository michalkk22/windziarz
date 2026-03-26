#pragma once

#include <string>

class FifoChannel
{
public:
    enum class Mode
    {
        Read,
        Write
    };

    FifoChannel(const std::string &path, Mode mode, bool create = false);
    ~FifoChannel();

    FifoChannel(const FifoChannel &) = delete;
    FifoChannel &operator=(const FifoChannel &) = delete;

    FifoChannel(FifoChannel &&other) noexcept;
    FifoChannel &operator=(FifoChannel &&other) noexcept;

    void sendInt(int value) const;
    int receiveInt() const;

private:
    std::string path_;
    int fd_{-1};
    bool owner_{false};
};