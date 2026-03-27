#pragma once

#include <string>

template <typename T>
class SharedMemory
{
public:
    SharedMemory(const std::string &name, bool create = false);
    ~SharedMemory();

    T *get();

private:
    std::string name_;
    int fd_;
    T *ptr_;
    bool owner_;
};