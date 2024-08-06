#pragma once
#include <inttypes.h>
namespace quartz
{
    class Size
    {

    public:
        uint64_t WIDTH;
        uint64_t HEIGHT;
        Size(uint64_t width, uint64_t height);
        Size(uint64_t size) : Size(size, size) {};
    };
}