#pragma once
#include <inttypes.h>

namespace crystal::geometry
{
    struct Size
    {
            uint64_t width;
            uint64_t height;
            Size(const uint64_t width, const uint64_t height) : width(width), height(height) {};
            explicit Size(const uint64_t size) : width(size), height(size) {};

            void changeTo(const uint64_t width, const uint64_t height){this->width = width; this->height = height;};

            [[nodiscard]] int getWidthAsInt() const;

            [[nodiscard]] int getHeightAsInt() const;
    };
} // namespace crystal::layout