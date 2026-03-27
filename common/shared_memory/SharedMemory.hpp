#pragma once

#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

template <typename T>
class SharedMemory
{
public:
    SharedMemory(const std::string &name, bool create = false)
        : name_(name), owner_(create)
    {
        int flags = create ? (O_CREAT | O_RDWR) : O_RDWR;

        fd_ = shm_open(name.c_str(), flags, 0666);
        if (fd_ == -1)
            throw std::runtime_error("shm_open failed");

        if (create)
        {
            ftruncate(fd_, sizeof(T));
        }

        ptr_ = static_cast<T *>(mmap(nullptr, sizeof(T),
                                     PROT_READ | PROT_WRITE,
                                     MAP_SHARED, fd_, 0));

        if (ptr_ == MAP_FAILED)
            throw std::runtime_error("mmap failed");
    }

    ~SharedMemory()
    {
        munmap(ptr_, sizeof(T));
        close(fd_);

        if (owner_)
        {
            shm_unlink(name_.c_str());
        }
    }

    T *get()
    {
        return ptr_;
    }

private:
    std::string name_;
    int fd_;
    T *ptr_;
    bool owner_;
};