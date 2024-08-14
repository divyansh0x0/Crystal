#pragma once
#include <inttypes.h>
namespace crystal
{
    class Size
    {

    public:
        uint64_t WIDTH;
        uint64_t HEIGHT;
        Size(uint64_t width, uint64_t height);
        Size(uint64_t size) : Size(size, size) {};
        void changeTo(uint64_t width, uint64_t height);
    };
}