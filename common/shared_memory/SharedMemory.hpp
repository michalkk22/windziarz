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
        : name(name), owner(create)
    {
        int flags = create ? (O_CREAT | O_RDWR) : O_RDWR;

        fd = shm_open(name.c_str(), flags, 0666);
        if (fd == -1)
            throw std::runtime_error("shm_open failed");

        if (create)
        {
            ftruncate(fd, sizeof(T));
        }

        ptr = static_cast<T *>(mmap(nullptr, sizeof(T),
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd, 0));

        if (ptr == MAP_FAILED)
            throw std::runtime_error("mmap failed");
    }

    ~SharedMemory()
    {
        munmap(ptr, sizeof(T));
        close(fd);

        if (owner)
        {
            shm_unlink(name.c_str());
        }
    }

    T *get()
    {
        return ptr;
    }

private:
    std::string name;
    int fd;
    T *ptr;
    bool owner;
};