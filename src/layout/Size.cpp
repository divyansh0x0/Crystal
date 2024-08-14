#include "crystal/layout/Size.h"
namespace crystal
{
    Size::Size(uint64_t width, uint64_t height)
    {
        WIDTH = width;
        HEIGHT = height;
    };
    void Size::changeTo(uint64_t width, uint64_t height)
    {
        WIDTH = width;
        HEIGHT = height;
    }
}