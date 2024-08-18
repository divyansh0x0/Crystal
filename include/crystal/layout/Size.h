#pragma once
#include <inttypes.h>
namespace crystal
{
    struct Size
    {
        uint64_t width;
        uint64_t height;
        Size(uint64_t width, uint64_t height) : width(width), height(height) {};
        Size(uint64_t size) : width(size), height(size) {};
        void changeTo(uint64_t width, uint64_t height) {this->width = width; this->height = height;};
    };
}